#include "game.h"
#include <iostream>

struct Particle { 
    Vector2 pos; 
    Vector2 vel; 
    Color tint;
    float life{0.0f}; 
    float rotation{0.0f}; 
    float scale{0.0f}; 
    int textureIndex{0}; 
};

std::array<Texture2D, 3> particleTextures;
std::array<Particle, 100> particles;

void Explode(Vector2 pos, Color tint, int textureIndex) {
    for (int i{0}; i < 10; i++) {
        for (auto& particle : particles) {
            if (particle.life <= 0) {
                particle = {pos, {static_cast<float>(GetRandomValue(-100,100)), static_cast<float>(GetRandomValue(-100,100))}, 
                            tint, 1.0f, static_cast<float>(GetRandomValue(0, 360)), 1.0f, textureIndex};
                break;
            }
        }
    }
}

void updateParticles() {

    for (auto& particle : particles) {
        if (particle.life > 0.0f) {

            particle.pos.x += particle.vel.x * GetFrameTime();
            particle.pos.y += particle.vel.y * GetFrameTime();
            particle.life -= GetFrameTime();
            particle.scale = particle.life; 

            if (particle.life <= 0.0f) {
                particle.tint.a = 0; 
            }

            Texture2D& texture = particleTextures[particle.textureIndex];
            Rectangle source = {0.0f, 0.0f, static_cast<float>(texture.width), static_cast<float>(texture.height)};
            Rectangle dest = {particle.pos.x, particle.pos.y, texture.width * particle.scale, texture.height * particle.scale};
            Vector2 origin = {texture.width * particle.scale * 0.5f, texture.height * particle.scale * 0.5f};
            DrawTexturePro(texture, source, dest, origin, particle.rotation, particle.tint);
        }
    }
}


void Game::DrawLight(Vector2 position, float radius, Color color)
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

    // light map
    RenderTexture2D lightMap = LoadRenderTexture(config::screenWidth, config::screenHeight);

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

    // particle (temp)
    particleTextures[0] = (LoadTexture("src/resources/Textures/blood1.png"));
    particleTextures[1] = (LoadTexture("src/resources/Textures/blood2.png"));
    particleTextures[2] = (LoadTexture("src/resources/Textures/blood3.png"));

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

        enemy.setEnemySpeed(2.0f);
        if(CheckCollisionRecs(playerAnimation.getBeamAttackRect(), enemy.getHitboxRect())) {
            enemy.takeDamage(0.25f); 
            enemy.setEnemySpeed(0.5f);
            if(enemy.getHealth() <= 0.0f){
                Explode(enemy.getPosition(), RED, rand() % particleTextures.size());
                enemy.setHealth(100.0f); 
                enemy.setPosition(Vector2{static_cast<float>(GetRandomValue(0, config::screenWidth)), static_cast<float>(GetRandomValue(0, config::screenWidth))}); 
            }
        }  

        BeginDrawing(); 
                    
            BeginMode2D(gameCamera.camera); 
                Utilities::drawBackground();
                fireAnimation.updateSprite();
                coinAnimation.updateSprite();
                playerAnimation.updateSprite();
                enemy.updateSprite();
                //enemy.chasePlayer(playerAnimation.getPosition());
                updateParticles(); 
            EndMode2D();   

            BeginTextureMode(lightMap);  
                ClearBackground(LIGHTGRAY); // screen tint (black for complete dark, etc.)
                BeginBlendMode(BLEND_ADDITIVE); 
                    //Vector2 screenPos = GetWorldToScreen2D(playerAnimation.getPosition(), gameCamera.camera);
                    //DrawLight(screenPos, 150, Color{255, 240, 200, 255});
                    //DrawLight(GetMousePosition(), 120, RED);
                    Vector2 screenPos2 = GetWorldToScreen2D(fireAnimation.getPosition(), gameCamera.camera);
                    float flicker = 140.0 + sin(GetTime() * 10.0) * 10.0;
                    DrawLight(screenPos2, flicker, ORANGE);
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
    soundSystem.~SoundSystem();
    UnloadMusicStream(music);

    CloseWindow();
}