#include "utilities.h"

namespace Utilities {

    void init(){
        InitWindow(config::screenWidth, config::screenHeight, "Raylib Program");
        SetWindowMinSize(config::screenWidth, config::screenHeight);
        SetTargetFPS(config::FPS);  
        SetWindowIcon(LoadImage("src/resources/Textures/space.png")); 
    }

    void drawBackground(){
        static Texture2D gameScreen = LoadTexture("src/resources/Textures/grassy.png");
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

    float toggleFullScreenWindow(){
        /*---------------------------------| 
        |  Only allow 16:9 raito           |
        |  (480x270) scale = 1.0f;         |
        |  (1920x1080) scale = 4.0f.       |
        |---------------------------------*/

        if(!IsWindowFullscreen()){
            int monitor = GetCurrentMonitor();
            SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
            ToggleFullscreen();
            return 4.0f; // 1920x1080 default fullscreen scale
        } 
        else{
            ToggleFullscreen();
            SetWindowSize(config::screenWidth, config::screenHeight);
            return 1.0f; // 480x270 default scale
        }

    }

    void DrawRectangleLinesPro(Rectangle rec, Vector2 origin, float rotation, Color color)
    {
        Vector2 corners[4];

        // Rectangle corners relative to origin
        Vector2 local[4] = {
            { -origin.x, -origin.y },                          // top-left
            { rec.width - origin.x, -origin.y },               // top-right
            { rec.width - origin.x, rec.height - origin.y },   // bottom-right
            { -origin.x, rec.height - origin.y }               // bottom-left
        };

        float rad = rotation*DEG2RAD;
        float sinR = sinf(rad);
        float cosR = cosf(rad);

        for (int i = 0; i < 4; i++)
        {
            corners[i].x = rec.x + local[i].x*cosR - local[i].y*sinR;
            corners[i].y = rec.y + local[i].x*sinR + local[i].y*cosR;
        }

        rlBegin(RL_LINES);
            rlColor4ub(color.r, color.g, color.b, color.a);

            rlVertex2f(corners[0].x, corners[0].y);
            rlVertex2f(corners[1].x, corners[1].y);

            rlVertex2f(corners[1].x, corners[1].y);
            rlVertex2f(corners[2].x, corners[2].y);

            rlVertex2f(corners[2].x, corners[2].y);
            rlVertex2f(corners[3].x, corners[3].y);

            rlVertex2f(corners[3].x, corners[3].y);
            rlVertex2f(corners[0].x, corners[0].y);
        rlEnd();
    }

}
