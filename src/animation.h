#pragma once

#include <raylib.h>
#include <array>
#include <cstdint>
#include <string>
#include "utilities.h"

class Animation {

    public: 

        Animation(const char* filePath, uint8_t frameCount, float positionX, float positionY, bool random);
        Animation();
        virtual ~Animation();
        
        virtual void drawSprite();
        virtual void updateSprite();
        virtual void drawHitbox();
        void animateSprite();
        void animateSpriteRandom();
    
        // GETTERS
        float getPositionX();
        float getPositionY();
        float getWidth();
        float getHeight();
        Vector2 getPosition();
        Rectangle getHitboxRect();

        // SETTERS
        void setPosition(Vector2 position);
        void setRotation(float rotation);
        
    protected:

        std::array<Texture2D, 10> m_animationTextures; // Textures for the animation (idle and moving left and right for now)
        Rectangle m_animationRect{0.0f}; // Source rectangle for the animation
        Rectangle m_hitboxRect{0.0f}; // Hitbox for the animation

        uint8_t m_frameCount{0}; 
        uint8_t m_currentFrame{0}; // Current frame of the animation
        bool m_random{false};
        float m_runningTime{0.0f};  // Time accumulator for the animation
        float m_animationTime{12.0f}; // Time animtion plays for - default 12.0f 83.33ms
        float m_updateTime{1.0f/m_animationTime}; // Time between frame updates
        float m_scale{1.0f};
        float m_positionX{0.0f}; 
        float m_positionY{0.0f}; 
        float m_rotation{0.0f};

};