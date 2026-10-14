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
};

static struct speaker_event events[EVENT_COUNT];
static SDL_AtomicInt event_write;             /* written by the game/interrupt threads */
static unsigned event_read;                   /* audio thread only */
static SDL_SpinLock event_lock;

static uint32_t state_divisor = 0x1000;       /* producer-side state */
static uint8_t  state_gate;

static SDL_AudioStream *stream;
static uint64_t playhead_ns;                  /* audio-thread state */
static uint32_t play_divisor = 0x1000;
static uint8_t  play_gate;
static double   phase;                        /* 0..1 within the square wave period */
static float    filtered;
static FILE    *wav_tap;                      /* DUKE1_AUDIO_WAV=file: a copy of the output, for tests */
static uint32_t wav_samples;

static void wav_header(FILE *f, uint32_t samples)
{
    uint32_t data = samples * 4u, riff = 36u + data, fmt = 16u, rate = SAMPLE_RATE, bps = SAMPLE_RATE * 4u;
    uint16_t pcm_float = 3, channels = 1, align = 4, bits = 32;
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

static void SDLCALL fill_audio(void *userdata, SDL_AudioStream *s, int additional_amount, int total_amount)
{
    float buffer[512];
    int samples = additional_amount / (int)sizeof(float);
    const uint64_t step_ns = 1000000000ull / SAMPLE_RATE;
    uint64_t target = SDL_GetTicksNS() - LATENCY_NS;
    (void)userdata;
    (void)total_amount;

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
                ++event_read;
            }
            float level = 0.0f;
            if (play_gate == 3) {
                double frequency = PIT_HZ / (double)play_divisor;
                if (frequency < 20000.0) {
                    phase += frequency / SAMPLE_RATE;
                    phase -= floor(phase);
                    level = phase < 0.5 ? VOLUME : -VOLUME;
                }
            }
            filtered += (level - filtered) * 0.45f;              /* soften the edges a little */
            buffer[i] = filtered;
            playhead_ns += step_ns;
        }
        SDL_PutAudioStreamData(s, buffer, n * (int)sizeof(float));
        if (wav_tap) {
            fwrite(buffer, sizeof(float), (size_t)n, wav_tap);
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
    spec.channels = 1;
    spec.freq = SAMPLE_RATE;
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
}
