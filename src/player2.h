#pragma once

#include <cmath>
#include "animation2.h"
#include "config.h"

class Player : public Animation {

    public:

        Player();
        ~Player();

        void drawSprite() override;
        void updateSprite() override;
        void drawHitbox() override;
        void setState(uint8_t newState);
        void handleKeyboardDash();
        void handleControllerDash();
        void handleKeyboardAttack();
        void handleControllerAttack();
        void handleKeyboardMovement();
        void handleControllerMovement();

        float getPlayerSpeed();
        Rectangle getAttackRect();
        void drawAttackHitbox();

        enum {IDLE,LEFT,RIGHT,UP,DOWN};

    private:
    
        // player variables
        float m_playerSpeed{1.55f}; 
    
        // frame variables
        bool m_idle{true}; 
        uint8_t m_direction{0}; 
        uint8_t m_lastDirection{0};

        // texture stuff
        Texture2D* m_currentTexture{nullptr};  // Pointer to current texture
        int8_t m_currentState{0};// Track current state of textures 

        // dash stuff
        float m_dashSpeed{800.0f};   // units per second
        float m_dashTime{0.1f};    // how long the dash lasts
        float m_dashTimer{0.0f};
        bool m_isDashing{false};

        // attack stuff
        Rectangle m_attackRect{0.0f};

        //controller stuff
        float m_axisX{0.0f};
        float m_axisY{0.0f};
        float m_axisXR{0.0f};
        float m_axisYR{0.0f};


};