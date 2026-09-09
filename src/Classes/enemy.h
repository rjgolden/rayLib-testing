#pragma once

#include <cmath>
#include <cstdint>
#include "animation.h"
#include "../Namespaces/assets.h"
#include "../Namespaces/global.h"

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
        void drawCircle();

        // getters
        float getHealth();
        Vector2 getCirclePos();

        // setters 
        void setHealth(float health);
        void setEnemySpeed(float speed);
        void setPositionRandom();
        void setPositionX(float pos, float deltaTime);
        void setPositionY(float pos, float deltaTime);

    private:
        float m_enemySpeed{2.0f};

        // health stuff
        float m_enemyHealth{25.0f};
        bool m_hurtFrameActive{false};
        Rectangle m_healthBarRect{0.0f}; 
        Texture2D m_enemyHurt;

        // steering
        Vector2 circlePos = {16.0f, 16.0f};
        float circleRadius = 20.0f;

};
