#pragma once
#include "raylib.h"

namespace Assets {

    extern Texture2D enemy;
    extern Texture2D enemyHurt;
    extern Texture2D flyEnemy;
    extern Texture2D fireAnimation;
    extern Texture2D coinAnimation;
    extern Texture2D defaultBeamX;
    extern Texture2D defaultBeamY;

    void loadAssets();
    void unloadAssets();

}
