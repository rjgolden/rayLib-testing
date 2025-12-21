#pragma once

#include <raylib.h>
#include <iostream>
#include <array>
#include <cstdint>

class Animation {

    public: 
        Animation(const char* filePath, uint8_t frameCount, float animationTime, float positionX, float positionY);
        Animation();
        ~Animation();
        
        void animateSprite();
        void drawSprite();
        void drawHitbox();
        void drawRectbox();
        void updateSprite();

        // GETTERS
        float getPositionX();
        float getPositionY(); 
        float getWidth();
        float getHeight();
        Rectangle getHitboxRect();

        // SETTERS
        void setPosition(float x, float y);
        
    protected:
        std::array<Texture2D, 3> m_animationTextures; // Textures for the animation (idle and moving left and right for now)
        Rectangle m_animationRect; // Source rectangle for the animation
        Rectangle m_hitboxRect; // Hitbox for the animation

        uint8_t m_currentFrame; // Current frame of the animation
        uint8_t m_frameCount; 
        float m_runningTime;  // Time accumulator for the animation
        float m_updateTime; // Time between frame updates
        float m_animationTime; // Time animtion plays for - default 12.0f 83.33ms
        float m_positionX; 
        float m_positionY; 
        float m_scale;

};