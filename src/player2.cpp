#include "player2.h"

/*-------------------------------*/
Player::Player(const char* filePath, const char* filePath2, const char* filePath3, uint8_t frameCount) {
    
    // vector Derived from animation class
    m_animationTextures[0] = LoadTexture(filePath); 
    m_animationTextures[1] = LoadTexture(filePath2);
    m_animationTextures[2] = LoadTexture(filePath3);
    m_currentTexture = &m_animationTextures[0]; // default is idle
    

    // Rectangles - Derived from animation class
    m_animationRect = { 0.0f, 0.0f, (float)m_animationTextures[0].width / 6.0f, (float)m_animationTextures[0].height }; 
    m_hitboxRect = { 0.0f, 0.0f, (float)m_animationTextures[0].width / 6.0f, (float)m_animationTextures[0].height };

    // frame stuff - All derived from animation class
    m_currentFrame = 0;
    m_frameCount = frameCount; 
    m_runningTime = 0.0f; 
    m_updateTime = 1.0f / 12.0f; 
    m_scale = 1.0f;

    // position and speed
    m_positionX = 320; // Derived from animation class
    m_positionY = 180; // Derived from animation class
    m_idle = true; 
    m_direction = 0;
    m_lastDirection = 0;
    m_playerSpeed = 1.15f; 

}

Player::~Player() {
    UnloadTexture(m_animationTextures[0]);
    UnloadTexture(m_animationTextures[1]);
    UnloadTexture(m_animationTextures[2]);
    std::cout << "Player Object Destroyed, textures succesfully unloaded.\n";
}

/*-------------------------------*/
void Player::drawSprite(){
    DrawTexturePro(*m_currentTexture, m_animationRect, {(float)m_positionX, (float)m_positionY, 32.0f, 32.0f}, {0.0f, 0.0f}, 0.0f, WHITE);
}

void Player::setState(uint8_t newState){

    if (newState != m_currentState) {  
        m_currentState = newState;
        m_lastDirection = newState;

        switch(newState) {
            case 1: m_currentTexture = &m_animationTextures[2]; break;  // left
            case 2: m_currentTexture = &m_animationTextures[1]; break;  // right
            default: m_currentTexture = &m_animationTextures[0]; break; // idle
        }
    }
}

void Player::updateSprite() {

    bool wasIdle = m_idle;
    int lastKey = 0;
    m_direction = 0;

    //---------------//
    if (IsKeyDown(KEY_D)){ 
        m_idle = false;
        m_direction = 2;
        m_positionX += m_playerSpeed;
        lastKey = KEY_D;
    }
    else if (IsKeyDown(KEY_A)) {
        m_idle = false;
        m_direction = 1; 
        m_positionX -= m_playerSpeed;
        lastKey = KEY_A;
    }
    if (IsKeyDown(KEY_W)){ 
        m_idle = false;
        m_direction = m_lastDirection;
        m_positionY -= m_playerSpeed;
        lastKey = KEY_W;
    }
    else if (IsKeyDown(KEY_S)){ 
        m_idle = false;
        m_direction = m_lastDirection;
        m_positionY += m_playerSpeed;
        lastKey = KEY_S;
    }

    if(IsKeyPressed(KEY_F)){
        m_direction = m_lastDirection;
        switch(lastKey){
            case KEY_W: m_positionY -= 40; break;
            case KEY_A: m_positionX -= 40; break;
            case KEY_S: m_positionY += 40; break;
            case KEY_D: m_positionX += 40; break;
        }
    }

    // Reset animation if state changed
    if (wasIdle != m_idle) {
        m_currentFrame = 0;
        m_runningTime = 0.0f;
    }
    
    //---------------//
    m_hitboxRect.x = m_positionX; 
    m_hitboxRect.y = m_positionY;


    //---------------//
    setState(m_direction);  
    animateSprite();
    drawSprite();
    drawHitbox();

}



