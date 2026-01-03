#include "utilities.h"

void Utilities::init(){
    InitWindow(config::screenWidth, config::screenHeight, "Raylib Program");
    SetWindowMinSize(config::screenWidth, config::screenHeight);
    SetTargetFPS(config::FPS);  
    SetWindowIcon(LoadImage("src/resources/Textures/space.png")); 
}

void Utilities::drawBackground(){
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

float Utilities::toggleFullScreenWindow(){
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
