#include "includes.h"

float ToggleFullscreenWindow(){

    /*---------------------------------| 
    |  Only allow 16:9 raito           |
    |  (640x320) scale = 1.0f;         |
    |  (1280x640) scale = 2.0f;        |
    |  (1920x1080) scale = 3.0f, etc.  |
    |---------------------------------*/

    if(!IsWindowFullscreen()){
        int monitor = GetCurrentMonitor();
        SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
        ToggleFullscreen();
        return 3.0f; // 1920x1080 default fullscreen scale
    } 
    else{
        ToggleFullscreen();
        SetWindowSize(config::screenWidth, config::screenHeight);
        return 1.0f; // 640x360 default scale
    }

}

void init(){
    InitWindow(config::screenWidth, config::screenHeight, "Raylib Program");
    SetWindowMinSize(config::screenWidth, config::screenHeight);
    SetTargetFPS(config::FPS);
    SetWindowOpacity(0.5);  
    SetWindowIcon(LoadImage("src/resources/Textures/space.png")); 
}

void drawBackground(){
    static Texture2D gameScreen = LoadTexture("src/resources/Textures/testScreen.png");
    static Texture2D spaceText = LoadTexture("src/resources/Textures/space.png");

    DrawTextureEx(gameScreen, {-640.0f, -360.0f}, 0.0f, 1.0f, WHITE);   // TOP LEFT

    // ABOVE (top row)
    DrawTextureEx(spaceText, {-640.0f, -720.0f}, 0.0f, 1.0f, WHITE);   // ABOVE TOP LEFT
    DrawTextureEx(spaceText, {0.0f,    -720.0f}, 0.0f, 1.0f, WHITE);   // ABOVE TOP
    DrawTextureEx(spaceText, {640.0f,  -720.0f}, 0.0f, 1.0f, WHITE);   // ABOVE TOP RIGHT

    // LEFT SIDE
    DrawTextureEx(spaceText, {-1280.0f, -360.0f}, 0.0f, 1.0f, WHITE);  // LEFT OF TOP LEFT
    DrawTextureEx(spaceText, {-1280.0f,   0.0f},  0.0f, 1.0f, WHITE);  // LEFT OF CENTER LEFT
    DrawTextureEx(spaceText, {-1280.0f, 360.0f},  0.0f, 1.0f, WHITE);  // LEFT OF BOTTOM LEFT

    // RIGHT SIDE
    DrawTextureEx(spaceText, {1280.0f, -360.0f}, 0.0f, 1.0f, WHITE);   // RIGHT OF TOP RIGHT
    DrawTextureEx(spaceText, {1280.0f,   0.0f},  0.0f, 1.0f, WHITE);   // RIGHT OF CENTER RIGHT
    DrawTextureEx(spaceText, {1280.0f, 360.0f},  0.0f, 1.0f, WHITE);   // RIGHT OF BOTTOM RIGHT

    // BELOW (bottom row)
    DrawTextureEx(spaceText, {-640.0f, 720.0f}, 0.0f, 1.0f, WHITE);    // BELOW BOTTOM LEFT
    DrawTextureEx(spaceText, {0.0f,    720.0f}, 0.0f, 1.0f, WHITE);    // BELOW BOTTOM
    DrawTextureEx(spaceText, {640.0f,  720.0f}, 0.0f, 1.0f, WHITE);    // BELOW BOTTOM RIGHT

    // CORNERS
    DrawTextureEx(spaceText, {-1280.0f, -720.0f}, 0.0f, 1.0f, WHITE);  // TOP LEFT CORNER
    DrawTextureEx(spaceText, {1280.0f,  -720.0f}, 0.0f, 1.0f, WHITE);  // TOP RIGHT CORNER
    DrawTextureEx(spaceText, {-1280.0f,  720.0f}, 0.0f, 1.0f, WHITE);  // BOTTOM LEFT CORNER
    DrawTextureEx(spaceText, {1280.0f,   720.0f}, 0.0f, 1.0f, WHITE);  // BOTTOM RIGHT CORNER

    //DrawTextureEx(top, {0.0f, -360.0f}, 0.0f, 1.0f, WHITE);  // UP
    //DrawTextureEx(right, {640.0f, 0.0f}, 0.0f, 1.0f, WHITE);   // RIGHT
    //DrawTextureEx(bottom, {0.0f, 360.0f}, 0.0f, 1.0f, WHITE);   // DOWN
    //DrawTextureEx(left, {-640.0f, 0.0f}, 0.0f, 1.0f, WHITE);  // LEFT
    //DrawTextureEx(mid, {0.0f, 0.0f}, 0.0f, 1.0f, WHITE);  // CENTER
    //DrawTextureEx(topRight, {640.0f, -360.0f}, 0.0f, 1.0f, WHITE);  // TOP RIGHT
    //DrawTextureEx(mid, {640.0f, 360.0f}, 0.0f, 1.0f, WHITE);   // BOTTOM RIGHT
    //DrawTextureEx(mid, {-640.0f, 360.0f}, 0.0f, 1.0f, WHITE);  // BOTTOM LEFT
    //DrawTextureEx(gameScreen, {-640.0f, -360.0f}, 0.0f, 1.0f, WHITE);   // TOP LEFT

}

int main(){ 
        
    //setup
    init();
    float scale{1.0f};  
    float deltaTime{0.0f};
    float centerX = static_cast<float>(config::screenWidth)/2.0f;
    float centerY = static_cast<float>(config::screenHeight)/2.0f;

    //animations & player
    Animation fireAnimation("src/resources/Animations/fireSpriteAnimation.png", 6, centerX, centerY);
    Animation coinAnimation("src/resources/Animations/coin_gold.png", 8, centerX, centerY);
    Player playerAnimation("src/resources/Animations/eyeball-Idle.png", "src/resources/Animations/eyeballMoveLeft.png", "src/resources/Animations/eyeballMoveRight.png", 
                            "src/resources/Animations/eyeballMoveUp.png", 8);

    // sound stuff
    SoundSystem soundSystem;  
    //Sound place = LoadSound("src/resources/Sounds/place.mp3");
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
            scale = ToggleFullscreenWindow();
            centerX = (static_cast<float>(config::screenWidth)*scale)/2.0f;
            centerY = (static_cast<float>(config::screenHeight)*scale)/2.0f;
            gameCamera.camera.zoom = scale;
            gameCamera.camera.offset = {centerX, centerY};
            std::cout << "CenterX: " << centerX << "\n";
            std::cout << "CenterY: " << centerY << "\n";
        }
        
        if(IsKeyDown(KEY_C)) {
            gameCamera.camera.target.x += (centerX - gameCamera.camera.target.x) * (1.1f * deltaTime);
            gameCamera.camera.target.y += (centerY - gameCamera.camera.target.y) * (1.1f * deltaTime);
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

        // FPS
        int intFPS = GetFPS();
        std::string stringFPS = std::to_string(intFPS);
        const char* FPS = stringFPS.c_str();
        
        BeginDrawing();
            ClearBackground(BLACK);                        
            BeginMode2D(gameCamera.camera);
                drawBackground();
                DrawText(FPS, 600, 0, 50, RED); 
                fireAnimation.updateSprite();
                coinAnimation.updateSprite();
                playerAnimation.updateSprite();
            EndMode2D();
        EndDrawing();
    }      
    
    CloseWindow();

}