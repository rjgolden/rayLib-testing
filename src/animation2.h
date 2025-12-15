#pragma once

#include <raylib.h>
#include <iostream>
#include <vector>
#include <cstdint>

class Animation {

    private:
        std::vector<Texture2D> m_animationTextures; // Textures for the animation (idle and moving left and right for now)
        Rectangle m_animationRect; // Source rectangle for the animation
        Rectangle m_hitboxRect; // Hitbox for the animation

        uint8_t m_currentFrame; // Current frame of the animation
        uint8_t m_frameCount; 
        float m_runningTime;  // Time accumulator for the animation
        float m_updateTime; // Time between frame updates
        float m_positionX; 
        float m_positionY; 
        float m_scale;

    public: 
        Animation(const char* filePath, uint8_t frameCount, float positionX, float positionY);
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
        void setScale(float scale);
};