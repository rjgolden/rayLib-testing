#include "gameCamera.h"
#include "config.h"

GameCamera::GameCamera(){
    camera = {0};
    camera.target = (Vector2) { config::screenWidth/2, config::screenHeight/2 };
    camera.offset = (Vector2) {(float)GetScreenWidth()  * 0.5f, (float)GetScreenHeight() * 0.5f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

GameCamera::~GameCamera() {}