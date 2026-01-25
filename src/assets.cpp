#include "assets.h"

namespace Assets {
    Texture2D enemy;
    Texture2D enemyHurt;
    Texture2D fireAnimation;
    Texture2D coinAnimation;
    Texture2D defaultBeamX;
    Texture2D defaultBeamY;

    void loadAssets() {
        enemy = LoadTexture("src/resources/Animations/enemyAnimation.png");
        enemyHurt = LoadTexture("src/resources/Textures/hoodyGuyEnemyHurt.png");
        fireAnimation = LoadTexture("src/resources/Animations/fireSpriteAnimation.png");
        coinAnimation = LoadTexture("src/resources/Animations/coin_gold.png");
        defaultBeamX = LoadTexture("src/resources/Animations/defaultBeamX.png");
        defaultBeamY = LoadTexture("src/resources/Animations/defaultBeamY.png");
    }

    void unloadAssets() {
        UnloadTexture(enemy);
        UnloadTexture(enemyHurt);
        UnloadTexture(fireAnimation);
        UnloadTexture(coinAnimation);
    }
}