#include "game.h"
#include <iostream>

void Game::runGame(){

    // setup
    Utilities::init();

    // animations
    Animation fireAnimation("src/resources/Animations/fireSpriteAnimation.png", 6, m_centerX, m_centerY, true);
    Animation coinAnimation("src/resources/Animations/coin_gold.png", 8, m_centerX, m_centerY, false);

    // player
    Player playerAnimation;

    // enemy
    Enemy enemy("src/resources/Animations/enemyAnimation.png", 6);

    // camera
    GameCamera gameCamera;

    // sound stuff
    SoundSystem soundSystem;  
    Sound coin = LoadSound("src/resources/Sounds/coin.mp3");

    // music
    Music music = LoadMusicStream("src/resources/Sounds/fireSound.mp3");
    PlayMusicStream(music);
    SetMusicVolume(music, 0.01f);
    music.looping = true;

    while (!WindowShouldClose())
    {   

        UpdateMusicStream(music);
        m_deltaTime = GetFrameTime();

        if(IsKeyPressed(KEY_F)) {
            m_scale = Utilities::toggleFullScreenWindow();
            m_centerX = (static_cast<float>(config::screenWidth)*m_scale)/2.0f;
            m_centerY = (static_cast<float>(config::screenHeight)*m_scale)/2.0f;
            gameCamera.camera.zoom = m_scale;
            gameCamera.camera.offset = {m_centerX, m_centerY};
        }
        
        if(IsKeyDown(KEY_C)) {
            gameCamera.camera.target.x += (m_centerX - gameCamera.camera.target.x) * (config::cameraLerp * m_deltaTime);
            gameCamera.camera.target.y += (m_centerY - gameCamera.camera.target.y) * (config::cameraLerp * m_deltaTime);
        }
        else{
            gameCamera.camera.target.x += ((playerAnimation.getPositionX() + 16.0f) - gameCamera.camera.target.x) * (playerAnimation.getPlayerSpeed() * m_deltaTime);
            gameCamera.camera.target.y += ((playerAnimation.getPositionY() + 32.0f) - gameCamera.camera.target.y) * (playerAnimation.getPlayerSpeed() * m_deltaTime);
        }

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            Vector2 worldPos = GetScreenToWorld2D({static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY())}, gameCamera.camera);
            Vector2 position = { worldPos.x - fireAnimation.getWidth()/2.0f, worldPos.y - fireAnimation.getHeight()/2.0f };
            coinAnimation.setPosition(position);
            PlaySound(coin);
        }

        enemy.setEnemySpeed(2.0f);
        if(CheckCollisionRecs(playerAnimation.getBeamAttackRect(), enemy.getHitboxRect())){
            std::cout << "hit\n";
            enemy.takeDamage(0.25f); 
            enemy.setEnemySpeed(0.5f);
            if(enemy.getHealth() <= 0.0f){
                enemy.setHealth(100.0f); 
                enemy.setPosition(Vector2{static_cast<float>(GetRandomValue(0, config::screenWidth)), static_cast<float>(GetRandomValue(0, config::screenWidth))}); 
            }
        }  

        BeginDrawing();
            ClearBackground(BLACK);                        
            BeginMode2D(gameCamera.camera);
                Utilities::drawBackground();
                fireAnimation.updateSprite();
                coinAnimation.updateSprite();
                playerAnimation.updateSprite();
                enemy.updateSprite();
                enemy.chasePlayer(playerAnimation.getPosition());
            EndMode2D();
        EndDrawing();
    }  
    
    // explicit destructor calls
    fireAnimation.~Animation();
    coinAnimation.~Animation();
    playerAnimation.~Player();
    soundSystem.~SoundSystem();
    UnloadMusicStream(music);

    CloseWindow();
}