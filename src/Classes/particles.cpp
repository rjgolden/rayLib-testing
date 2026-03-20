#include "particles.h"

Particles::Particles(){
    m_particleTextures[0] = (LoadTexture("src/resources/Textures/blood1.png"));
    m_particleTextures[1] = (LoadTexture("src/resources/Textures/blood2.png"));
    m_particleTextures[2] = (LoadTexture("src/resources/Textures/blood3.png"));
}

Particles::~Particles(){
    UnloadTexture(m_particleTextures[0]);
    UnloadTexture(m_particleTextures[1]);
    UnloadTexture(m_particleTextures[2]);
}

void Particles::explode(Vector2 pos, Color tint, int textureIndex) {
    for (int i{0}; i < 10; i++) {
        for (Particle& particle : m_particles) {
            if (particle.life <= 0) {
                particle = {pos, {static_cast<float>(GetRandomValue(-100,100)), static_cast<float>(GetRandomValue(-100,100))}, 
                            tint, 1.0f, static_cast<float>(GetRandomValue(0, 360)), 1.0f, textureIndex};
                break;
            }
        }
    }
}

void Particles::updateParticles() {

    for (Particle& particle : m_particles) {
        if (particle.life > 0.0f) {

            particle.pos.x += particle.vel.x * GetFrameTime();
            particle.pos.y += particle.vel.y * GetFrameTime();
            particle.life -= GetFrameTime();
            particle.scale = particle.life; 

            if (particle.life <= 0.0f) {
                particle.tint.a = 0; 
            }

            Texture2D& texture = m_particleTextures[particle.textureIndex];
            Rectangle source = {0.0f, 0.0f, static_cast<float>(texture.width), static_cast<float>(texture.height)};
            Rectangle dest = {particle.pos.x, particle.pos.y, texture.width * particle.scale, texture.height * particle.scale};
            Vector2 origin = {texture.width * particle.scale * 0.5f, texture.height * particle.scale * 0.5f};
            DrawTexturePro(texture, source, dest, origin, particle.rotation, particle.tint);
        }
    }
}