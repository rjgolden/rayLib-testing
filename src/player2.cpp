#include "player2.h"

/*-------------------------------*/
Player::Player(const char* filePath, const char* filePath2, const char* filePath3, int frameCount) {
    m_animationTextures.push_back(LoadTexture(filePath)); 
    m_animationTextures.push_back(LoadTexture(filePath2));
    m_animationTextures.push_back(LoadTexture(filePath3));
    m_currentTexture = &m_animationTextures[0]; // default is idle
    

    // Rectangles 
    m_animationRect = { 0.0f, 0.0f, (float)m_animationTextures[0].width / 6.0f, (float)m_animationTextures[0].height }; 
    m_hitboxRect = { 0.0f, 0.0f, (float)m_animationTextures[0].width / 6.0f, (float)m_animationTextures[0].height };

    // frame stuff
    m_currentFrame = 0; // 0 default frame
    m_frameCount = frameCount;
    m_runningTime = 0.0f; 
    m_updateTime = 1.0f / 12.0f; 
    m_scale = 1.0f;

    // position and speed
    m_positionX = 320; 
    m_positionY = 180; 
    m_idle = true; 
    m_direction = 0;
    m_lastDirection = 0;
    m_playerSpeed = 3.0f; 
}

Player::~Player() {
     if(!m_animationTextures.empty()){
        UnloadTexture(m_animationTextures.back());
        m_animationTextures.pop_back();
    }
    std::cout << "Player Object Destroyed, texture succesfully unloaded.\n";
}

/*-------------------------------*/
void Player::drawSprite(){
    DrawTexturePro(*m_currentTexture, m_animationRect, {(float)m_positionX*m_scale, (float)m_positionY*m_scale, 32.0f*m_scale, 32.0f*m_scale}, {0.0f, 0.0f}, 0.0f, WHITE);
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
    m_direction = 0;

    //---------------//
    if (IsKeyDown(KEY_D)){ 
        m_idle = false;
        m_direction = 2;
        m_positionX += m_playerSpeed;
    }
    else if (IsKeyDown(KEY_A)) {
        m_idle = false;
        m_direction = 1; 
        m_positionX -= m_playerSpeed;
    }
    if (IsKeyDown(KEY_W)){ 
        m_idle = false;
        m_direction = m_lastDirection;
        m_positionY -= m_playerSpeed;
    }
    else if (IsKeyDown(KEY_S)){ 
        m_idle = false;
        m_direction = m_lastDirection;
        m_positionY += m_playerSpeed;
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

    //---------------//
    drawHitbox();

}

bool Player::isAnimationComplete() {
    // Check if the current frame is the last frame of the animation
    return (m_currentFrame >= m_frameCount);
}

//----------------------------------------------//

void Player::setPlayerSpeed(float speed) {
    m_playerSpeed = speed;
}

