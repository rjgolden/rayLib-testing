#pragma once
#include "animation2.h"
#include "config.h"

class Player : public Animation {

    public:

        Player(const char* filePath, const char* filePath2, const char* filePath3, const char* filePath4, uint8_t frameCount);
        ~Player();

        void drawSprite() override;
        void updateSprite() override;
        void drawHitbox() override;
        void setState(uint8_t newState);
        void handleDash();
        void handleAttack();
        void handleMovement();

        float getPlayerSpeed();
        Rectangle getAttackRect();
        void drawAttackHitbox();

    private:
    
        // player variables
        float m_playerSpeed{1.55f}; 
        int m_lastKey{0};
    
        // frame variables
        bool m_idle{true}; 
        uint8_t m_direction{0}; 
        uint8_t m_lastDirection{0};

        // texture stuff
        Texture2D* m_currentTexture;  // Pointer to current texture
        int8_t m_currentState{0};// Track current state of textures 

        // dash stuff
        float m_dashSpeed{800.0f};   // units per second
        float m_dashTime{0.1f};    // how long the dash lasts
        float m_dashTimer{0.0f};
        bool m_isDashing{false};

        Rectangle m_attackRect{0.0f};

};