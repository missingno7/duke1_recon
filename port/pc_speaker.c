/* pc_speaker.c - the PC speaker: PIT channel 2 square wave gated by port 0x61.

   The game's timer interrupt (144 Hz) reprograms channel 2 and switches the gate bits for
   every step of a sound effect.  Each change is recorded with its time; the audio callback
   replays the changes at those times, a fixed delay behind, so note lengths come out exact
   instead of being rounded to audio buffer boundaries. */

#include "pc_internal.h"
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
static SDL_AtomicInt game_frame;
static SDL_SpinLock game_frame_lock;
static int last_timer_counter;
static int have_timer_counter;
static int tested_frame;
static uint64_t tested_time_ns;
static int tested_position_valid;
static int tested_world_x;
static int tested_scroll_x;
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

static void observe_game_counter(int tick_counter)
{
    SDL_LockSpinlock(&game_frame_lock);
    if (have_timer_counter && tick_counter < last_timer_counter)
        SDL_SetAtomicInt(&game_frame, SDL_GetAtomicInt(&game_frame) + 1);
    last_timer_counter = tick_counter;
    have_timer_counter = 1;
    SDL_UnlockSpinlock(&game_frame_lock);
}

void pc_speaker_note_game_tick(int tick_counter)
{
    observe_game_counter(tick_counter);
}

void pc_speaker_note_view_test(int world_x, int scroll_x, int tick_counter)
{
    observe_game_counter(tick_counter);
    tested_world_x = world_x;
    tested_scroll_x = scroll_x;
    tested_frame = SDL_GetAtomicInt(&game_frame);
    tested_time_ns = SDL_GetTicksNS();
    tested_position_valid = 1;
}

float pc_speaker_view_pan(int tick_counter)
{
    observe_game_counter(tick_counter);
    /* An actor's view test and its sound request are microseconds apart: use a test only if it
       is that fresh, and only once.  (Menus and intros never reset the tick counter, so the
       frame number alone would let a test from earlier gameplay pan their sounds.) */
    if (!tested_position_valid || tested_frame != SDL_GetAtomicInt(&game_frame)
            || SDL_GetTicksNS() - tested_time_ns > 20000000ull)
        return 0.0f;
    tested_position_valid = 0;
    /* is_world_position_outside_view admits [scroll, scroll + 29); pan around
       that original view's centre, not the widescreen renderer's camera. */
    return clamp_pan(((float)tested_world_x - (float)tested_scroll_x - 14.5f) / 14.5f);
}

void pc_speaker_set_next_pan(float pan)
{
    SDL_LockSpinlock(&event_lock);
    requested_pan = clamp_pan(pan);
    SDL_UnlockSpinlock(&event_lock);
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
