#include "game.h"
#include "particles.h"
#include <iostream>
#include <vector>

void Game::drawLight(Vector2 position, float radius, Color color)
{
    DrawCircleGradient(
        static_cast<int>(position.x) + 16,
        static_cast<int>(position.y) + 32,
        radius * m_scale,
        color,
        BLANK
    );
}

void Game::runGame(){

    // setup
    Utilities::init();
    Assets::loadAssets();

    // light map
    RenderTexture2D lightMap = LoadRenderTexture(config::screenWidth, config::screenHeight);

    // animations
    Animation fireAnimation(Assets::fireAnimation, 6, m_centerX, m_centerY, true);
    Animation coinAnimation(Assets::coinAnimation, 8, m_centerX, m_centerY, false);

    // player
    Player playerAnimation;
    
    // enemies
    std::vector<Enemy> enemies;
    enemies.reserve(10);
    for(int i{0}; i<5; i++){
        enemies.emplace_back(Enemy(Assets::enemy, 6));
    }
    for(int i{0}; i<5; i++){
        enemies.emplace_back(Enemy(Assets::flyEnemy, 6));
    }

    // camera
    GameCamera gameCamera;

    // sound stuff
    SoundSystem initSoundSystem;  
    Sound coin = LoadSound("src/resources/Sounds/coin.mp3");

    // music
    Music music = LoadMusicStream("src/resources/Sounds/fireSound.mp3");
    PlayMusicStream(music);
    SetMusicVolume(music, 0.01f);
    music.looping = true;

    // particles
    Particles particles;


    // temp
    int enemiesKilled{0};

    while (!WindowShouldClose())
    {   

        UpdateMusicStream(music);
        m_deltaTime = GetFrameTime();

        if(IsKeyPressed(KEY_F)) {

            m_scale = Utilities::toggleFullScreenWindow();

            m_centerX = (static_cast<float>(config::screenWidth)*m_scale)/2.0f;
            m_centerY = (static_cast<float>(config::screenHeight)*m_scale)/2.0f;

            lightMap = LoadRenderTexture(config::screenWidth*static_cast<int>(m_scale), config::screenHeight*static_cast<int>(m_scale));

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

        for(Enemy &enemy : enemies){
            enemy.setEnemySpeed(2.0f);
            if(CheckCollisionRecs(playerAnimation.getBeamAttackRect(), enemy.getHitboxRect())) {
                enemy.takeDamage(0.25f); 
                enemy.setEnemySpeed(0.5f);
            }
            if(enemy.getHealth() <= 0.0f){
                enemiesKilled++;
                particles.explode(enemy.getPosition(), RED, rand() % particles.m_particleTextures.size());
                enemy.setHealth(20.0f); 
                enemy.setPositionRandom();
            }
        }

        BeginDrawing(); 
                    
            BeginMode2D(gameCamera.camera); 

                Utilities::drawBackground();
                fireAnimation.updateSprite();
                coinAnimation.updateSprite();
                playerAnimation.updateSprite();
                for(Enemy &enemy : enemies){
                    enemy.updateSprite();
                    enemy.chasePlayer(playerAnimation.getPosition());
                }
                particles.updateParticles();
                
            EndMode2D(); 

            std::string enemiesKilledStr = std::to_string(enemiesKilled);
            const char* enemiesKilledCStr = enemiesKilledStr.c_str();
            DrawText("Enemies Killed: ", 20, 20, 20, YELLOW);
            DrawText(enemiesKilledCStr, 180, 20, 20, YELLOW);

            BeginTextureMode(lightMap);  

                ClearBackground(GRAY); // screen tint (black for complete dark, etc.)
                BeginBlendMode(BLEND_ADDITIVE); 
                    Vector2 screenPos = GetWorldToScreen2D(playerAnimation.getPosition(), gameCamera.camera);
                    drawLight(screenPos, 150, Color{255, 240, 200, 255});
                    Vector2 screenPos2 = GetWorldToScreen2D(fireAnimation.getPosition(), gameCamera.camera);
                    float flicker = 140.0 + sin(GetTime() * 10.0) * 10.0;
                    drawLight(screenPos2, flicker, ORANGE);
                EndBlendMode();

            EndTextureMode(); 

            BeginBlendMode(BLEND_MULTIPLIED); 
                DrawTextureRec(lightMap.texture, Rectangle{0.0f, 0.0f, static_cast<float>(lightMap.texture.width), -static_cast<float>(lightMap.texture.height)}, Vector2{0, 0}, RAYWHITE);
            EndBlendMode(); 

        EndDrawing(); 
    } 
    
    // explicit destructor calls
    fireAnimation.~Animation();
    coinAnimation.~Animation();
    playerAnimation.~Player();
    particles.~Particles();
    initSoundSystem.~SoundSystem();
    Assets::unloadAssets();
    UnloadMusicStream(music);

    CloseWindow();
}