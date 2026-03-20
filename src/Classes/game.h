#pragma once

#include "../Namespaces/utilities.h"
#include "../Namespaces/assets.h"
#include "player.h"
#include "animation.h"
#include "soundSystem.h"
#include "gameCamera.h"
#include "enemy.h"

class Game {

    public:
        void runGame();
        void drawLight(Vector2 position, float radius, Color color);

    private:
        float m_scale{1.0f};  
        float m_deltaTime{0.0f};
        float m_centerX{static_cast<float>(Global::halfScreenWidth)};
        float m_centerY{static_cast<float>(Global::halfScreenHeight)};

};