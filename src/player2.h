#pragma once
#include "animation2.h"

class Player : public Animation {

    public:

        Player(const char* filePath, const char* filePath2, const char* filePath3, const char* filePath4,  const char* filePath5, uint8_t frameCount);
        ~Player();

        void drawSprite();
        void setState(uint8_t newState);
        void handleDash();
        void handleMovement();
        void updateSprite();
        float getPlayerSpeed();

    private:
    
        // player variables
        float m_playerSpeed; 
        int m_lastKey;
    
        // frame variables
        bool m_idle; 
        uint8_t m_direction; 
        uint8_t m_lastDirection;

        // texture stuff
        Texture2D* m_currentTexture;  // Pointer to current texture
        int8_t m_currentState;// Track current state of textures 

        // dash stuff
        float m_dashSpeed;   // units per second
        float m_dashTime;    // how long the dash lasts
        float m_dashTimer;
        bool m_isDashing;

};