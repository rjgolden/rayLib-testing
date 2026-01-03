#include "player2.h"

/*-------------------------------*/
Player::Player(const char* filePath, const char* filePath2, const char* filePath3, const char* filePath4, uint8_t frameCount) {
    
    // vector Derived from animation class
    m_animationTextures[0] = LoadTexture(filePath); 
    m_animationTextures[1] = LoadTexture(filePath2);
    m_animationTextures[2] = LoadTexture(filePath3);
    m_animationTextures[3] = LoadTexture(filePath4);
    m_currentTexture = &m_animationTextures[0]; // default is idle
    
    // Rectangles - Derived from animation class
    m_animationRect = { 0.0f, 0.0f, static_cast<float>(m_animationTextures[0].width) / static_cast<float>(frameCount), static_cast<float>(m_animationTextures[0].height) }; 
    m_hitboxRect = { 0.0f, 0.0f, static_cast<float>(m_animationTextures[0].width) / static_cast<float>(frameCount), static_cast<float>(m_animationTextures[0].height) };

    // frame stuff - All derived from animation class
    m_frameCount = frameCount;  

    // position and speed, Variables derived from animation class
    m_positionX = static_cast<float>(config::screenWidth) / 2.0f;
    m_positionY = static_cast<float>(config::screenHeight) / 2.0f; 

}

Player::~Player() {
    UnloadTexture(m_animationTextures[0]);
    UnloadTexture(m_animationTextures[1]);
    UnloadTexture(m_animationTextures[2]);
    UnloadTexture(m_animationTextures[3]); 
    std::cout << "Player Object Destroyed, textures succesfully unloaded.\n";
}

/*-------------------------------*/
void Player::drawSprite() {
    DrawTexturePro(*m_currentTexture, m_animationRect, {static_cast<float>(m_positionX), static_cast<float>(m_positionY), static_cast<float>(m_animationTextures[0].width) / static_cast<float>(m_frameCount), static_cast<float>(m_animationTextures[0].height)}, {0.0f, 0.0f}, 0.0f, WHITE);
}

void Player::drawHitbox() {
    DrawEllipseLines(m_positionX + 16.5f, m_positionY + 32.0f, 8.0f, 12.0f, RED);                         // Draw circle outline
}

void Player::drawAttackHitbox() {
    DrawRectangleLines(m_attackRect.x, m_attackRect.y, m_attackRect.width, m_attackRect.height, GREEN);
};

void Player::setState(uint8_t newState){

    m_updateTime = 1.0f / m_animationTime;

    if (newState != m_currentState) {  
        m_currentState = newState;
        m_lastDirection = newState;

        switch(newState) {
            case 1: m_currentTexture = &m_animationTextures[1]; m_animationTime = 12.0; break;  // left
            case 2: m_currentTexture = &m_animationTextures[2]; m_animationTime = 12.0; break;  // right
            case 3: m_currentTexture = &m_animationTextures[3]; m_animationTime = 12.0; break;  // up
            case 4: m_currentTexture = &m_animationTextures[0]; m_animationTime = 12.0; break;  // down
            default: m_currentTexture = &m_animationTextures[0]; m_animationTime = 6.0; break; // idle 
        }
    }

}

void Player::handleMovement(){

    bool wasIdle = m_idle; 
    //m_direction = 0; uncomment if idle default is wanted
    
    //---------------//
    if (IsKeyDown(KEY_A)) {
        m_idle = false;
        m_direction = 1; 
        m_positionX -= m_playerSpeed;
        m_lastKey = KEY_A;
    }
    else if (IsKeyDown(KEY_D)){ 
        m_idle = false;
        m_direction = 2;
        m_positionX += m_playerSpeed;
        m_lastKey = KEY_D;
    }
    if (IsKeyDown(KEY_W)){ 
        m_idle = false;
        m_direction = 3;
        m_positionY -= m_playerSpeed;
        m_lastKey = KEY_W;
    }
    else if (IsKeyDown(KEY_S)){ 
        m_idle = false;
        m_direction = 4;
        m_positionY += m_playerSpeed;
        m_lastKey = KEY_S;
    }

    // Reset animation if state changed
    if (wasIdle != m_idle) {
        m_currentFrame = 0;
        m_runningTime = 0.0f;
    }
    
}

void Player::handleDash(){

    if(IsKeyPressed(KEY_SPACE) && !m_isDashing){
        m_isDashing = true;
        m_dashTimer = m_dashTime;
    }

    float deltaTime = GetFrameTime();

    if (m_isDashing) {

        float move = m_dashSpeed * deltaTime;

        // UP & DIAGONAL UPs
        if(IsKeyDown(KEY_W)) m_positionY -= move;
        else if(IsKeyDown(KEY_W) && IsKeyDown(KEY_D)) { m_positionY -= move; m_positionX += move; }
        else if(IsKeyDown(KEY_W) && IsKeyDown(KEY_A)) { m_positionY -= move; m_positionX -= move; }

        // DOWN & DIAGONAL DOWNS
        if(IsKeyDown(KEY_S)) m_positionY += move;
        else if(IsKeyDown(KEY_S) && IsKeyDown(KEY_D)) { m_positionY += move; m_positionX += move; }
        else if(IsKeyDown(KEY_S) && IsKeyDown(KEY_A)) { m_positionY += move; m_positionX -= move; }

        // LEFT & RIGHT
        if(IsKeyDown(KEY_A)) m_positionX -= move;
        if(IsKeyDown(KEY_D)) m_positionX += move;

        m_dashTimer -= deltaTime;
        if (m_dashTimer <= 0.0f) {
            m_isDashing = false;
        }
    }

    m_hitboxRect.x = m_positionX; 
    m_hitboxRect.y = m_positionY;
}

void Player::handleAttack() {

    m_attackRect.x = m_positionX + 16.0f;
    m_attackRect.y = m_positionY + 16.0f; 
    m_attackRect.width = 5.0f; 
    m_attackRect.height = 5.0f; 

    if(IsKeyDown(KEY_RIGHT)){
        m_idle = false;
        m_direction = 2;
        m_attackRect.x += 11.0f; 
        m_attackRect.width = 55.0f;
        m_attackRect.height = 15.0f;
    }
    else if(IsKeyDown(KEY_LEFT)){
        m_idle = false;
        m_direction = 1; 
        m_attackRect.x -= 64.0f;
        m_attackRect.width = 55.0f; 
        m_attackRect.height = 15.0f; 
    }
    else if(IsKeyDown(KEY_UP)){
        m_idle = false;
        m_direction = 3; 
        m_attackRect.x -= 8.0f;
        m_attackRect.y -= 40.0f;
        m_attackRect.width = 15.0f;
        m_attackRect.height = 55.0f;
    }
    else if(IsKeyDown(KEY_DOWN)){
        m_idle = false;
        m_direction = 0; 
        m_attackRect.x -= 8.0f;
        m_attackRect.y += 20.0f;
        m_attackRect.width = 15.0f; 
        m_attackRect.height = 55.0f; 
    }
    drawAttackHitbox();

}

void Player::updateSprite() {

    handleMovement();
    handleAttack();
    handleDash();
    setState(m_direction);  
    animateSprite();
    drawSprite();
    drawHitbox();

}

// GETTERS
float Player::getPlayerSpeed(){
    return m_playerSpeed;
}
