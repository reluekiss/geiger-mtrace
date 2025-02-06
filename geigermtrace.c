#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>
#include "raylib.h"

typedef void* (*malloc_t)(size_t);
static malloc_t real_malloc = NULL;

typedef void (*free_t)(void *);
static free_t real_free = NULL;

static pthread_mutex_t beepMutex = PTHREAD_MUTEX_INITIALIZER;
static int beepPending = 0;
static double lastBeepTime = 0.0;
const double beepCooldown = 0.0; 

const float beepFrequency = 1000.0f;
const float beepDuration = 0.025f;
const int sampleRate = 44100;
const int beepFrameCount = (int)(beepDuration * sampleRate);

static int currentBeepFrames = 0;
static float sinePhase = 0.0f;

void AudioInputCallback(void *buffer, unsigned int frames)
{
    short *d = (short *)buffer;
    float phaseIncrement = beepFrequency / sampleRate;
    for (unsigned int i = 0; i < frames; i++)
    {
        short sample = 0;
        if (currentBeepFrames > 0)
        {
            sample = (short)(32000 * sinf(2 * PI * sinePhase));
            sinePhase += phaseIncrement;
            if (sinePhase >= 1.0f) sinePhase -= 1.0f;
            currentBeepFrames--;
        }
        else
        {
            pthread_mutex_lock(&beepMutex);
            if (beepPending) {
                currentBeepFrames = beepFrameCount;
                sinePhase = 0.0f;
                beepPending = 0;
            }
            pthread_mutex_unlock(&beepMutex);
        }
        d[i] = sample;
    }
}

void* audio_thread_func(void* arg)
{
    InitAudioDevice();
    AudioStream stream = LoadAudioStream(sampleRate, 16, 1);
    SetAudioStreamCallback(stream, AudioInputCallback);
    PlayAudioStream(stream);

    while (1) { sleep(10); }

    UnloadAudioStream(stream);
    CloseAudioDevice();
    return NULL;
}

__attribute__((constructor))
void init_audio()
{
    pthread_t tid;
    pthread_create(&tid, NULL, audio_thread_func, NULL);
}

void* malloc(size_t size)
{
    if (!real_malloc)
        real_malloc = (malloc_t)dlsym(RTLD_NEXT, "malloc");

    double now = time(NULL);
    pthread_mutex_lock(&beepMutex);
    if ((now - lastBeepTime) >= beepCooldown) {
        beepPending = 1;
        lastBeepTime = now;
    }
    pthread_mutex_unlock(&beepMutex);

    return real_malloc(size);
}

void free(void *ptr)
{
    if (!real_free)
        real_free = (free_t)dlsym(RTLD_NEXT, "free");

    double now = time(NULL);
    pthread_mutex_lock(&beepMutex);
    if ((now - lastBeepTime) >= beepCooldown) {
        beepPending = 1;
        lastBeepTime = now;
    }
    pthread_mutex_unlock(&beepMutex);
}
