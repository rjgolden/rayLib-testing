#pragma once
#include "raylib.h"
#include <array>

class Particles {

    public:

        Particles();
        ~Particles();

        void explode(Vector2 pos, Color tint, int textureIndex);
        void updateParticles();

        struct Particle { 
            Vector2 pos; 
            Vector2 vel; 
            Color tint;
            float life{0.0f}; 
            float rotation{0.0f}; 
            float scale{0.0f}; 
            int textureIndex{0}; 
        };

        std::array<Texture2D, 3> m_particleTextures;
        std::array<Particle, 100> m_particles;

};