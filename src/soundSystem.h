#pragma once
#include "raylib.h"
#include <cmath>

class SoundSystem {

    public:
        SoundSystem();
        ~SoundSystem();

        static void ProcessAudio(void *buffer, unsigned int frames);

    private:
        static float m_exponent;                 // Audio exponentiation value
        static float m_averageVolume[400];   // Average volume history
        static float m_volume;  // Volume multiplier (0.0 = mute, 1.0 = original volume)

};