#include "utilities.h"

int main(){ 
        
    //setup
    Utilities utils;
    utils.init();
    float scale{1.0f};  
    float deltaTime{0.0f};
    float centerX = static_cast<float>(config::screenWidth)/2.0f;
    float centerY = static_cast<float>(config::screenHeight)/2.0f;

    //animations
    Animation fireAnimation("src/resources/Animations/fireSpriteAnimation.png", 6, centerX, centerY, true);
    Animation coinAnimation("src/resources/Animations/coin_gold.png", 8, centerX, centerY, false);

    //player
    Player playerAnimation;

    // sound stuff
    SoundSystem soundSystem;  
    Sound coin = LoadSound("src/resources/Sounds/coin.mp3");

    // music
    Music music = LoadMusicStream("src/resources/Sounds/fireSound.mp3");
    PlayMusicStream(music);
    SetMusicVolume(music, 0.01f);
    music.looping = true;

    // Camera
    GameCamera gameCamera;

    while (!WindowShouldClose())
    {   

        UpdateMusicStream(music);
        deltaTime = GetFrameTime();

        if(IsKeyPressed(KEY_F)) {
            scale = utils.toggleFullScreenWindow();
            centerX = (static_cast<float>(config::screenWidth)*scale)/2.0f;
            centerY = (static_cast<float>(config::screenHeight)*scale)/2.0f;
            gameCamera.camera.zoom = scale;
            gameCamera.camera.offset = {centerX, centerY};
        }
        
        if(IsKeyDown(KEY_C)) {
            gameCamera.camera.target.x += (centerX - gameCamera.camera.target.x) * (config::cameraLerp * deltaTime);
            gameCamera.camera.target.y += (centerY - gameCamera.camera.target.y) * (config::cameraLerp * deltaTime);
        }
        else{
            gameCamera.camera.target.x += (playerAnimation.getPositionX() - gameCamera.camera.target.x) * (playerAnimation.getPlayerSpeed() * deltaTime);
            gameCamera.camera.target.y += (playerAnimation.getPositionY() - gameCamera.camera.target.y) * (playerAnimation.getPlayerSpeed() * deltaTime);
        }

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            Vector2 worldPos = GetScreenToWorld2D({static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY())}, gameCamera.camera);
            Vector2 position = { worldPos.x - fireAnimation.getWidth()/2.0f, worldPos.y - fireAnimation.getHeight()/2.0f };
            coinAnimation.setPosition(position);
            PlaySound(coin);
        }

        BeginDrawing();
            ClearBackground(BLACK);                        
            BeginMode2D(gameCamera.camera);
                utils.drawBackground();
                fireAnimation.updateSprite();
                coinAnimation.updateSprite();
                playerAnimation.updateSprite();
            EndMode2D();
        EndDrawing();
    }      
    
    CloseWindow();

}