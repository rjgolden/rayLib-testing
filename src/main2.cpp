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
    SetTargetFPS(60);
    SetWindowIcon(LoadImage("src/resources/Textures/space.png")); 
}

void drawBackground(){
    static Texture2D gameScreen = LoadTexture("src/resources/Textures/space.png");
    DrawTextureEx(gameScreen, {0.0f, -360.0f}, 0.0f, 1.0f, WHITE);  // UP
    DrawTextureEx(gameScreen, {640.0f, 0.0f}, 0.0f, 1.0f, WHITE);   // RIGHT
    DrawTextureEx(gameScreen, {0.0f, 360.0f}, 0.0f, 1.0f, WHITE);   // DOWN
    DrawTextureEx(gameScreen, {-640.0f, 0.0f}, 0.0f, 1.0f, WHITE);  // LEFT
    DrawTextureEx(gameScreen, {0.0f, 0.0f}, 0.0f, 1.0f, WHITE);  // CENTER
    DrawTextureEx(gameScreen, {640.0f, -360.0f}, 0.0f, 1.0f, WHITE);  // TOP RIGHT
    DrawTextureEx(gameScreen, {-640.0f, -360.0f}, 0.0f, 1.0f, WHITE);   // TOP LEFT
    DrawTextureEx(gameScreen, {640.0f, 360.0f}, 0.0f, 1.0f, WHITE);   // BOTTOM RIGHT
    DrawTextureEx(gameScreen, {-640.0f, 360.0f}, 0.0f, 1.0f, WHITE);  // BOTTOM LEFT
}

int main(){ 
        
    //setup
    init();
    float scale = 1.0f;  
    float deltaTime = 0.0f;
    float centerX = (float)config::screenWidth/2.0f;
    float centerY = (float)config::screenHeight/2.0f;

    //animations & player
    Animation fireAnimation("src/resources/Animations/fireSpriteAnimation.png", 6, 12.0f, centerX, centerY);
    Animation coinAnimation("src/resources/Animations/coin_gold.png", 8, 14.0f, centerX, centerY);
    Player playerAnimation("src/resources/Animations/idle.png", "src/resources/Animations/runLeft.png", "src/resources/Animations/runRight.png", 
                            "src/resources/Animations/runUp.png", "src/resources/Animations/runDown.png", 6);

    // sound stuff
    SoundSystem soundSystem;  
    //Sound place = LoadSound("src/resources/Sounds/place.mp3");
    Sound coin = LoadSound("src/resources/Sounds/coin.mp3");

    // music
    Music music = LoadMusicStream("src/resources/Sounds/fireSound.mp3");
    PlayMusicStream(music);
    SetMusicVolume(music, 0.05f);
    music.looping = true;

    // Camera
    GameCamera gameCamera;

    while (!WindowShouldClose())
    {   

        UpdateMusicStream(music);
        deltaTime = GetFrameTime();

        if(IsKeyPressed(KEY_F)) {
            scale = ToggleFullscreenWindow();
            centerX = ((float)config::screenWidth*scale)/2.0f;
            centerY = ((float)config::screenHeight*scale)/2.0f;
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
            Vector2 worldPos = GetScreenToWorld2D((Vector2){(float)GetMouseX(), (float)GetMouseY()}, gameCamera.camera);
            Vector2 position = { worldPos.x - fireAnimation.getWidth()/2.0f, worldPos.y - fireAnimation.getHeight()/2.0f };
            coinAnimation.setPosition(position);
            PlaySound(coin);
        }

        // FPS
        int intFPS = GetFPS();
        std::string stringFPS = std::to_string(intFPS);
        const char* FPS = stringFPS.c_str();

        BeginDrawing();
            ClearBackground(RED);                        
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