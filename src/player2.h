#pragma once
#include "animation2.h"

class Player: public Animation {

    private:
    
        // player variables
        float m_playerSpeed; 
    
        // frame variables
        bool m_idle; 
        uint8_t m_direction; 
        uint8_t m_lastDirection;

        // texture stuff
        Texture2D* m_currentTexture;  // Pointer to current texture
        int8_t m_currentState;// Track current state of textures 


    public:
        Player(const char* filePath, const char* filePath2, const char* filePath3, int frameCount);
        ~Player();

        void drawSprite();
        void setState(uint8_t newState);
        void updateSprite();

};