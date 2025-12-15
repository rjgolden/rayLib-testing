#include <memory>
#include "animation2.h"

float ToggleFullscreenWindow(){

    if(!IsWindowFullscreen()){
        int monitor = GetCurrentMonitor();
        SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
        ToggleFullscreen();
        return 3.0f;
    } 
    else{
        ToggleFullscreen();
        SetWindowSize(640, 360);
        return 1.0f;
    }

}

void checkAnimation(Animation& anime){

    std::cout << "Animation Position: (" << anime.getPositionX() << "," << anime.getPositionY() << ")\n";
    std::cout << "Animation Width: " << anime.getWidth() << "\n";
    std::cout << "Animation Height: " << anime.getHeight() << "\n";

}

int main(){

    constexpr int screenWidth = 640;
    constexpr int screenHeight = 360;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Raylib Program");
    SetWindowMinSize(screenWidth, screenHeight);
    SetTargetFPS(60);
    SetWindowIcon(LoadImage("src/resources/Textures/space.png"));                              

    float scale = 1.0f;
    Animation fireAnimation("src/resources/Animations/fireSpriteAnimation.png", 6, screenWidth/2, screenHeight/2);
    Texture2D gameScreen = LoadTexture("src/resources/Textures/space.png"); 
    
    while (!WindowShouldClose())
    {   

        if(IsKeyPressed(KEY_SPACE)) {
            scale = ToggleFullscreenWindow();
            fireAnimation.setScale(scale);
            checkAnimation(fireAnimation);
        }

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            int x = GetMouseX();
            int y = GetMouseY();
            std::cout << "Mouse position: (" << x << "," << y << ")\n";
            fireAnimation.setPosition((float)x/scale - fireAnimation.getWidth()/2,(float)y/scale - fireAnimation.getHeight()/2);
        }

        BeginDrawing();
            ClearBackground(WHITE);
            DrawTextureEx(gameScreen, {0.0f, 0.0f}, 0.0f, scale, WHITE);
            fireAnimation.updateSprite();
        EndDrawing();
    }      
    CloseWindow();
}
    


