#pragma once
#include "utilities.h"
#include "player.h"
#include "animation.h"
#include "soundSystem.h"
#include "config.h"
#include "gameCamera.h"

class Game {

    public:
        Game();
        ~Game();
        void runGame();

    private:
        float m_scale{1.0f};  
        float m_deltaTime{0.0f};
        float m_centerX{static_cast<float>(config::halfScreenWidth)};
        float m_centerY{static_cast<float>(config::halfScreenHeight)};

};