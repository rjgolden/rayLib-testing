#pragma once
#include "raylib.h"

namespace Assets {

    inline Texture2D enemy;
    inline Texture2D enemyHurt;
    inline Texture2D flyEnemy;
    inline Texture2D fireAnimation;
    inline Texture2D coinAnimation;
    inline Texture2D defaultBeamX;
    inline Texture2D defaultBeamY;

    void loadAssets();
    void unloadAssets();

}
