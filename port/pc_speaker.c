/* pc_speaker.c - the PC speaker: PIT channel 2 square wave gated by port 0x61.

   The game's timer interrupt (144 Hz) reprograms channel 2 and switches the gate bits for
   every step of a sound effect.  Each change is recorded with its time; the audio callback
   replays the changes at those times, a fixed delay behind, so note lengths come out exact
   instead of being rounded to audio buffer boundaries. */

#include "pc_internal.h"
#include "scene.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PIT_HZ          1193182.0
#define SAMPLE_RATE     44100
#define LATENCY_NS      40000000ull          /* replay delay behind the game */
#define EVENT_COUNT     4096u
#define VOLUME          0.18f

struct speaker_event {
    uint64_t time_ns;
    uint32_t divisor;                         /* channel 2 reload value, 0 = 65536 */
    uint8_t  gate;                            /* port 0x61 bits 0 (timer gate) and 1 (speaker data) */
    float    pan;
};

static struct speaker_event events[EVENT_COUNT];
static SDL_AtomicInt event_write;             /* written by the game/interrupt threads */
static SDL_AtomicInt speaker_volume = { 80 };
static unsigned event_read;                   /* audio thread only */
static SDL_SpinLock event_lock;

static uint32_t state_divisor = 0x1000;       /* producer-side state */
static uint8_t  state_gate;

static SDL_AudioStream *stream;
static uint64_t playhead_ns;                  /* audio-thread state */
static uint32_t play_divisor = 0x1000;
static uint8_t  play_gate;
static float    play_pan;
static float    play_left_gain = 1.0f;
static float    play_right_gain = 1.0f;
static int      play_stereo_mode = -1;
static double   phase;                        /* 0..1 within the square wave period */
static float    filtered;
static FILE    *wav_tap;                      /* DUKE1_AUDIO_WAV=file: a copy of the output, for tests */
static uint32_t wav_samples;
static uint16_t wav_channels = 1;
static SDL_AtomicInt stereo_enabled;
static SDL_AtomicInt wav_recording;
static float requested_pan;
static float state_pan;

static void wav_header(FILE *f, uint32_t samples);

static float clamp_pan(float pan)
{
    if (pan < -1.0f) return -1.0f;
    if (pan > 1.0f) return 1.0f;
    return pan;
}

void pc_speaker_set_stereo(int on)
{
    SDL_SetAtomicInt(&stereo_enabled, on != 0);
    /* The audio stream starts before the data-folder settings are loaded. Until
       the first sound, update the WAV format to the selected startup setting. */
    if (wav_tap && !SDL_GetAtomicInt(&wav_recording)) {
        wav_channels = on ? 2 : 1;
        wav_header(wav_tap, 0);
    }
}

void pc_speaker_set_source_world_x(int16_t world_x, int16_t scroll_x)
{
    /* Pan by the source's position in the visible view (half-tile units): the original
       playfield is 26 wide from scroll_x; widescreen shows the scene's wide view. */
    float left = (float)scroll_x;
    float width = (float)((PLAYFIELD_X1 - PLAYFIELD_X0) / 8);
    float pan = 0.0f;
    if (world_x != PC_SOUND_SOURCE_CENTRE) {
        int canvas_width = scene_wide_canvas_width();
        if (canvas_width > SCENE_WIDTH) {
            left = (float)scene_wide_view_left(scroll_x, canvas_width) / 8.0f;
            width = (float)(canvas_width - SCENE_WIDTH + PLAYFIELD_X1 - PLAYFIELD_X0) / 8.0f;
        }
        pan = ((float)world_x - left - width * 0.5f) / (width * 0.5f);
    }
    SDL_LockSpinlock(&event_lock);
    requested_pan = clamp_pan(pan);
    SDL_UnlockSpinlock(&event_lock);
}

void pc_speaker_reset(void)
{
    SDL_LockSpinlock(&event_lock);
    memset(events, 0, sizeof(events));
    SDL_SetAtomicInt(&event_write, 0);
    event_read = 0;
    state_divisor = 0x1000;
    state_gate = 0;
    requested_pan = state_pan = 0.0f;
    SDL_UnlockSpinlock(&event_lock);
    playhead_ns = 0;
    play_divisor = 0x1000;
    play_gate = 0;
    play_pan = 0.0f;
    play_left_gain = play_right_gain = 1.0f;
    phase = 0.0;
    filtered = 0.0f;
    if (stream) (void)SDL_ClearAudioStream(stream);
}

void pc_speaker_begin_sound(void)
{
    SDL_LockSpinlock(&event_lock);
    state_pan = requested_pan;
    SDL_UnlockSpinlock(&event_lock);
    SDL_SetAtomicInt(&wav_recording, 1);
}

static void wav_header(FILE *f, uint32_t samples)
{
    uint32_t data = samples * (uint32_t)wav_channels * 4u, riff = 36u + data, fmt = 16u;
    uint32_t rate = SAMPLE_RATE, bps = SAMPLE_RATE * (uint32_t)wav_channels * 4u;
    uint16_t pcm_float = 3, channels = wav_channels, align = (uint16_t)(wav_channels * 4u), bits = 32;
    fseek(f, 0, SEEK_SET);
    fwrite("RIFF", 1, 4, f); fwrite(&riff, 4, 1, f); fwrite("WAVEfmt ", 1, 8, f);
    fwrite(&fmt, 4, 1, f); fwrite(&pcm_float, 2, 1, f); fwrite(&channels, 2, 1, f);
    fwrite(&rate, 4, 1, f); fwrite(&bps, 4, 1, f); fwrite(&align, 2, 1, f); fwrite(&bits, 2, 1, f);
    fwrite("data", 1, 4, f); fwrite(&data, 4, 1, f);
    fseek(f, 0, SEEK_END);
}

static void push_event(void)
{
    SDL_LockSpinlock(&event_lock);
    unsigned w = (unsigned)SDL_GetAtomicInt(&event_write);
    events[w % EVENT_COUNT].time_ns = SDL_GetTicksNS();
    events[w % EVENT_COUNT].divisor = state_divisor;
    events[w % EVENT_COUNT].gate = state_gate;
    events[w % EVENT_COUNT].pan = state_pan;
    SDL_SetAtomicInt(&event_write, (int)(w + 1));
    SDL_UnlockSpinlock(&event_lock);
}

void pc_speaker_set_divisor(uint32_t divisor)
{
    state_divisor = divisor ? divisor : 65536u;
    push_event();
}

void pc_speaker_set_gate(uint8_t port61)
{
    uint8_t gate = port61 & 3u;
    if (gate == state_gate)
        return;
    state_gate = gate;
    push_event();
}

void pc_speaker_set_volume(int percent) {
    if (percent < 0) percent = 0; if (percent > 100) percent = 100; SDL_SetAtomicInt(&speaker_volume, percent);
}

static void SDLCALL fill_audio(void *userdata, SDL_AudioStream *s, int additional_amount, int total_amount)
{
    float buffer[1024];
    int samples = additional_amount / (int)(sizeof(float) * 2u);
    int stereo = SDL_GetAtomicInt(&stereo_enabled);
    float volume = VOLUME * (float)SDL_GetAtomicInt(&speaker_volume) / 100.0f;
    const uint64_t step_ns = 1000000000ull / SAMPLE_RATE;
    uint64_t target = SDL_GetTicksNS() - LATENCY_NS;
    (void)userdata;
    (void)total_amount;

    if (play_stereo_mode != stereo) {
        play_stereo_mode = stereo;
        if (stereo) {
            float angle = (play_pan + 1.0f) * 0.7853981633974483f;
            play_left_gain = cosf(angle);
            play_right_gain = sinf(angle);
        } else {
            play_left_gain = 1.0f;
            play_right_gain = 1.0f;
        }
    }

    /* Keep the playhead near "now - latency": after a stall, skip ahead instead of lagging. */
    if (playhead_ns == 0 || playhead_ns + 4 * LATENCY_NS < target || playhead_ns > target + LATENCY_NS)
        playhead_ns = target;

    while (samples > 0) {
        int n = samples < 512 ? samples : 512;
        for (int i = 0; i < n; ++i) {
            unsigned w = (unsigned)SDL_GetAtomicInt(&event_write);
            if (w - event_read > EVENT_COUNT)                     /* overrun: drop the oldest */
                event_read = w - EVENT_COUNT;
            while (event_read != w && events[event_read % EVENT_COUNT].time_ns <= playhead_ns) {
                play_divisor = events[event_read % EVENT_COUNT].divisor;
                play_gate = events[event_read % EVENT_COUNT].gate;
                play_pan = events[event_read % EVENT_COUNT].pan;
                if (stereo) {
                    float angle = (play_pan + 1.0f) * 0.7853981633974483f;
                    play_left_gain = cosf(angle);
                    play_right_gain = sinf(angle);
                }
                ++event_read;
            }
            float level = 0.0f;
            if (play_gate == 3) {
                double frequency = PIT_HZ / (double)play_divisor;
                if (frequency < 20000.0) {
                    double increment = frequency / SAMPLE_RATE;
                    phase += increment;
                    phase -= floor(phase);
                    double correction = 0.0;
                    double t = phase;
                    if (t < increment) {
                        double x = t / increment;
                        correction = x + x - x * x - 1.0;
                    } else if (t > 1.0 - increment) {
                        double x = (t - 1.0) / increment;
                        correction = x * x + x + x + 1.0;
                    }
                    t = phase + 0.5;
                    if (t >= 1.0) t -= 1.0;
                    if (t < increment) {
                        double x = t / increment;
                        correction -= x + x - x * x - 1.0;
                    } else if (t > 1.0 - increment) {
                        double x = (t - 1.0) / increment;
                        correction -= x * x + x + x + 1.0;
                    }
                    level = (float)((phase < 0.5 ? 1.0 : -1.0) + correction) * volume;
                }
            }
            filtered += (level - filtered) * 0.45f;              /* soften the edges a little */
            buffer[i * 2] = filtered * play_left_gain;
            buffer[i * 2 + 1] = filtered * play_right_gain;
            playhead_ns += step_ns;
        }
        SDL_PutAudioStreamData(s, buffer, n * (int)(sizeof(float) * 2u));
        if (wav_tap && SDL_GetAtomicInt(&wav_recording)) {
            if (wav_channels == 2) {
                fwrite(buffer, sizeof(float), (size_t)n * 2u, wav_tap);
            } else {
                for (int i = 0; i < n; ++i) {
                    float mono = stereo
                        ? (buffer[i * 2] + buffer[i * 2 + 1]) * 0.5f
                        : buffer[i * 2];
                    fwrite(&mono, sizeof(mono), 1, wav_tap);
                }
            }
            wav_samples += (uint32_t)n;
            wav_header(wav_tap, wav_samples);
        }
        samples -= n;
    }
}

int pc_speaker_init(void)
{
    SDL_AudioSpec spec;
    if (!SDL_InitSubSystem(SDL_INIT_AUDIO))
        return 0;
    spec.format = SDL_AUDIO_F32;
    spec.channels = 2;
    spec.freq = SAMPLE_RATE;
    wav_channels = SDL_GetAtomicInt(&stereo_enabled) ? 2 : 1;
    if (getenv("DUKE1_AUDIO_WAV") && (wav_tap = fopen(getenv("DUKE1_AUDIO_WAV"), "wb")) != NULL)
        wav_header(wav_tap, 0);
    stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, fill_audio, NULL);
    if (!stream)
        return 0;
    return SDL_ResumeAudioStreamDevice(stream);
}

void pc_speaker_shutdown(void)
{
    if (stream)
        SDL_DestroyAudioStream(stream);
    stream = NULL;
    if (wav_tap) {
        wav_header(wav_tap, wav_samples);
        fclose(wav_tap);
        wav_tap = NULL;
    }
}
