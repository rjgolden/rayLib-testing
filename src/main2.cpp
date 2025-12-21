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
        return 3.0f; // 1920 x 1080 default fullscreen scale
    } 
    else{
        ToggleFullscreen();
        SetWindowSize(640, 360);
        return 1.0f; // 640x360 default scale
    }

}

void checkAnimation(Animation& anim){

    std::cout << "Animation Position: (" << anim.getPositionX() << "," << anim.getPositionY() << ")\n";
    std::cout << "Animation Width: " << anim.getWidth() << "\n";
    std::cout << "Animation Height: " << anim.getHeight() << "\n";

}

void setup(){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE); // only for testing purposes 
    InitWindow(config::screenWidth, config::screenHeight, "Raylib Program");
    SetWindowMinSize(config::screenWidth, config::screenHeight);
    SetTargetFPS(60);
    SetWindowIcon(LoadImage("src/resources/Textures/space.png")); 
}

int main(){ 
                         
    setup();
    float scale = 1.0f;  
    Texture2D gameScreen = LoadTexture("src/resources/Textures/space.png");
    Texture2D gameScreen2 = LoadTexture("src/resources/Textures/desert.png");
    Animation fireAnimation("src/resources/Animations/fireSpriteAnimation.png", 6, config::screenWidth/2, config::screenHeight/2);
    Player hoodyAnimation("src/resources/Animations/hoodyIdleAnimation.png", "src/resources/Animations/hoodyRunAnimation.png", "src/resources/Animations/hoodyRunAnimation2.png", 6);

    // sound stuff
    SoundSystem soundSystem;  
    Sound place = LoadSound("src/resources/Sounds/place.mp3");

    // music
    Music music = LoadMusicStream("src/resources/Sounds/fireSound.mp3");
    PlayMusicStream(music);
    SetMusicVolume(music, 0.05f);
    music.looping = true;

    // Camera
    Camera2D m_camera;
    m_camera = {0};
    m_camera.target = (Vector2) { hoodyAnimation.getPositionX(), hoodyAnimation.getPositionY() };
    m_camera.offset = (Vector2) {(float)GetScreenWidth()  * 0.5f, (float)GetScreenHeight() * 0.5f};
    m_camera.rotation = 0.0f;
    m_camera.zoom = scale;

    while (!WindowShouldClose())
    {   

        UpdateMusicStream(music);

        m_camera.target = (Vector2){ hoodyAnimation.getPositionX(), hoodyAnimation.getPositionY() };
        if(IsKeyPressed(KEY_SPACE)) {
            scale = ToggleFullscreenWindow();
            fireAnimation.setScale(scale);
            hoodyAnimation.setScale(scale);
            m_camera.zoom = scale;
            m_camera.offset = {(float)GetScreenWidth()  * 0.5f, (float)GetScreenHeight() * 0.5f};
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            Vector2 worldPos = GetScreenToWorld2D((Vector2){(float)GetMouseX(), (float)GetMouseY()}, m_camera);
            int x = worldPos.x - fireAnimation.getWidth()/2;
            int y = worldPos.y - fireAnimation.getWidth()/2;
            fireAnimation.setPosition(x,y);
            PlaySound(place);
        }

        BeginDrawing();
            ClearBackground(WHITE);
            BeginMode2D(m_camera);
                DrawTextureEx(gameScreen, {0.0f, 0.0f}, 0.0f, 1.0f, WHITE);
                DrawTextureEx(gameScreen2, {640.0f, 0.0f}, 0.0f, 1.0f, WHITE);
                hoodyAnimation.updateSprite();
                fireAnimation.updateSprite();
            EndMode2D();
        EndDrawing();
    }      
    CloseWindow();
}