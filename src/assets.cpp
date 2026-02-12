#include "assets.h"

namespace Assets {

     inline Texture2D enemy;
     inline Texture2D enemyHurt;
     inline Texture2D flyEnemy;
     inline Texture2D fireAnimation;
     inline Texture2D coinAnimation;
     inline Texture2D defaultBeamX;
     inline Texture2D defaultBeamY;

    void loadAssets() {
        enemy = LoadTexture("src/resources/Animations/enemyAnimation.png");
        enemyHurt = LoadTexture("src/resources/Textures/hoodyGuyEnemyHurt.png");
        flyEnemy = LoadTexture("src/resources/Animations/flyEnemy.png");
        fireAnimation = LoadTexture("src/resources/Animations/fireSpriteAnimation.png");
        coinAnimation = LoadTexture("src/resources/Animations/coin_gold.png");
        defaultBeamX = LoadTexture("src/resources/Animations/defaultBeamX.png");
        defaultBeamY = LoadTexture("src/resources/Animations/defaultBeamY.png");
    }

    void unloadAssets() {
        UnloadTexture(enemy);
        UnloadTexture(enemyHurt);
        UnloadTexture(flyEnemy);
        UnloadTexture(fireAnimation);
        UnloadTexture(coinAnimation);
        UnloadTexture(defaultBeamX);
        UnloadTexture(defaultBeamY);
    }

}