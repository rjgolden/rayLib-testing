#pragma once
#include "animation2.h"

class Player: public Animation {

    private:

        // textures
        std::vector<Texture2D> m_animationTextures;

        // player variables
        float m_playerSpeed; 
    
        // frame variables
        bool m_idle; 
        unsigned m_direction; 
        unsigned m_lastDirection;
        Texture2D* m_currentTexture;  // Pointer to current texture
        int m_currentState;// Track current state of textures 


    public:

        Player(const char* filePath, const char* filePath2, const char* filePath3, int frameCount);
        ~Player();

        void drawSprite();
        void setState(uint8_t newState);
        void updateSprite();
        bool isAnimationComplete();

        //getters and setters
        Rectangle getAttackRect();
        int getHealth();
        void setPlayerSpeed(float speed);
        void setHealth(int health);
};