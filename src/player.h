#pragma once

#include <cmath>
#include <memory>
#include "animation.h"
#include "config.h"

class Player : public Animation {

    public:

        Player();
        ~Player();

        // sprite
        void drawSprite() override;
        void updateSprite() override;
        void drawHitbox() override;
        void drawAttackHitbox();
        void setState(uint8_t newState);
        
        // keyboard
        void handleKeyboardDash();
        void handleKeyboardAttack();
        void handleKeyboardMovement();

        // controller
        void handleControllerDash();
        void handleControllerAttack();
        void handleControllerMovement();

        // getters
        float getPlayerSpeed();
        Rectangle getBeamAttackRect();

        // states
        enum {IDLE,LEFT,RIGHT,UP,DOWN, ATTACK_RIGHT, ATTACK_LEFT, ATTACK_DOWN};

    private:
    
        // player variables
        float m_playerSpeed{1.55f}; 
    
        // frame variables
        bool m_idle{true}; 
        uint8_t m_state{0}; 

        // texture stuff
        Texture2D* m_currentTexture{nullptr};  // pointer to current texture
        int8_t m_currentState{0};// track current state of textures 

        // dash stuff
        float m_dashSpeed{800.0f};   // pixels per second
        float m_dashTime{0.1f};    // how long the dash lasts
        float m_dashTimer{0.0f}; // uses dashTime each frame
        bool m_isDashing{false};

        //controller stuff
        float m_axisX{0.0f};
        float m_axisY{0.0f};
        float m_axisXR{0.0f};
        float m_axisYR{0.0f};

        // animation & sound stuff
        std::array<Texture2D, 10> m_animationTextures;
        Animation m_beamAnimationX;
        Animation m_beamAnimationY;
        Vector2 m_defaultBeamSizeX{0.0f};
        Vector2 m_defaultBeamSizeY{0.0f};

};