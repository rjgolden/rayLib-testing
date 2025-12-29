#include "gameCamera.h"

GameCamera::GameCamera(){
    camera = {0};
    Vector2 middle ={ (float)config::screenWidth/2.0f, (float)config::screenHeight/2.0f };
    camera.target = middle;
    camera.offset = middle;
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}