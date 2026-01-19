#include "utilities.h"

namespace Utilities {

    void init(){
        InitWindow(config::screenWidth, config::screenHeight, "Test");
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

    void DrawRectangleLinesPro(Rectangle rec, Vector2 origin, Color color, float rotation) {

        Vector2 topLeft = { 0 };
        Vector2 topRight = { 0 };
        Vector2 bottomLeft = { 0 };
        Vector2 bottomRight = { 0 };

        if (rotation == 0.0f)
        {
            float x = rec.x - origin.x;
            float y = rec.y - origin.y;

            topLeft = (Vector2){ x, y };
            topRight = (Vector2){ x + rec.width, y };
            bottomLeft = (Vector2){ x, y + rec.height };
            bottomRight = (Vector2){ x + rec.width, y + rec.height };
        }
        else
        {
            float sinRotation = sinf(rotation*DEG2RAD);
            float cosRotation = cosf(rotation*DEG2RAD);

            float x = rec.x;
            float y = rec.y;
            float dx = -origin.x;
            float dy = -origin.y;

            topLeft.x = x + dx*cosRotation - dy*sinRotation;
            topLeft.y = y + dx*sinRotation + dy*cosRotation;

            topRight.x = x + (dx + rec.width)*cosRotation - dy*sinRotation;
            topRight.y = y + (dx + rec.width)*sinRotation + dy*cosRotation;

            bottomLeft.x = x + dx*cosRotation - (dy + rec.height)*sinRotation;
            bottomLeft.y = y + dx*sinRotation + (dy + rec.height)*cosRotation;

            bottomRight.x = x + (dx + rec.width)*cosRotation - (dy + rec.height)*sinRotation;
            bottomRight.y = y + (dx + rec.width)*sinRotation + (dy + rec.height)*cosRotation;
        }

        rlBegin(RL_LINES);
            rlColor4ub(color.r, color.g, color.b, color.a);

            // Top
            rlVertex2f(topLeft.x, topLeft.y);
            rlVertex2f(topRight.x, topRight.y);

            // Right
            rlVertex2f(topRight.x, topRight.y);
            rlVertex2f(bottomRight.x, bottomRight.y);

            // Bottom
            rlVertex2f(bottomRight.x, bottomRight.y);
            rlVertex2f(bottomLeft.x, bottomLeft.y);

            // Left
            rlVertex2f(bottomLeft.x, bottomLeft.y);
            rlVertex2f(topLeft.x, topLeft.y);
        rlEnd();
    }

}
