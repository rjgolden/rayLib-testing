#include <memory>
#include "animation2.h"
#include "player2.h"
#include "config.h"

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

void checkAnimation(Animation& anim){

    std::cout << "Animation Position: (" << anim.getPositionX() << "," << anim.getPositionY() << ")\n";
    std::cout << "Animation Width: " << anim.getWidth() << "\n";
    std::cout << "Animation Height: " << anim.getHeight() << "\n";

}

int main(){ 

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(config::screenWidth, config::screenHeight, "Raylib Program");
    SetWindowMinSize(config::screenWidth, config::screenHeight);
    SetTargetFPS(60);
    SetWindowIcon(LoadImage("src/resources/Textures/space.png"));                              

    float scale = 1.0f;
    Animation fireAnimation("src/resources/Animations/fireSpriteAnimation.png", 6, config::screenWidth/2, config::screenHeight/2);
    Texture2D gameScreen = LoadTexture("src/resources/Textures/space.png");
    Player hoodyAnimation("src/resources/Animations/hoodyIdleAnimation.png", "src/resources/Animations/hoodyRunAnimation.png", "src/resources/Animations/hoodyRunAnimation2.png", 6);

    
    while (!WindowShouldClose())
    {   

        if(IsKeyPressed(KEY_SPACE)) {
            scale = ToggleFullscreenWindow();
            fireAnimation.setScale(scale);
            hoodyAnimation.setScale(scale);
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
            hoodyAnimation.updateSprite();
        EndDrawing();
    }      
    CloseWindow();
}
    


