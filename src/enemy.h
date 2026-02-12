#pragma once

#include <cmath>
#include <cstdint>
#include "animation.h"
#include "assets.h"

class Enemy : public Animation {
        
    public:
        Enemy(Texture2D texture, uint8_t frameCount);
        Enemy();
        ~Enemy() = default;

        void updateSprite() override;
        void chasePlayer(Vector2 position);
        void takeDamage(float damage);
        void drawHealthBar();
        void drawHurtFrame();

        // getters
        float getHealth();

        // setters 
        void setHealth(float health);
        void setEnemySpeed(float speed);
        void setPositionRandom();

    private:
        float m_enemySpeed{2.0f};

        // health stuff
        float m_enemyHealth{25.0f};
        bool m_hurtFrameActive{false};
        Rectangle m_healthBarRect{0.0f}; 
        Texture2D m_enemyHurt;

};
