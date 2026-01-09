#include "enemy.h"
#include <cmath>

/*-------------------------------*/
Enemy::Enemy(const char* filePath, uint8_t frameCount){

    // Load textures
    m_animationTextures[0] = LoadTexture(filePath); 
    m_enemyHurt = LoadTexture("src/resources/Textures/hoodyGuyEnemyHurt.png"); // Load enemy hurt texture

    m_defaultWidth = static_cast<float>(m_animationTextures[0].width) / static_cast<float>(frameCount);
    m_defaultHeight = static_cast<float>(m_animationTextures[0].height);

    // Rectangles 
    m_animationRect = { 0.0f, 0.0f, m_defaultWidth, m_defaultHeight }; 
    m_hitboxRect = { 0.0f, 0.0f, m_defaultWidth, m_defaultHeight };
    m_healthBarRect = { 0.0f, 0.0f, m_defaultWidth, 10.0f }; // Health bar rectangle

    m_frameCount = frameCount;
    
    // position and speed
    m_positionX = GetRandomValue(0, config::screenWidth); 
    m_positionY = GetRandomValue(0, config::screenHeight); 

}

Enemy::~Enemy() {
    UnloadTexture(m_animationTextures[0]);
}

/*-------------------------------*/
void Enemy::chasePlayer(Vector2 position){
    float dx = position.x - m_positionX;
    float dy = position.y - m_positionY;
    float length = std::sqrt(dx*dx + dy*dy);
    if (length > 0) {
        dx /= length;
        dy /= length;
    }
    m_positionX += dx * m_enemySpeed;
    m_positionY += dy * m_enemySpeed;
}

void Enemy::takeDamage(float damage) {
    m_hurtFrameActive = true; // Activate hurt frame
    m_enemyHealth -= damage;
    if (m_enemyHealth < 0.0f) {
        m_enemyHealth = 0.0f; // Prevent negative health
    }
}

void Enemy::drawHealthBar(){
    // Draw background
    DrawRectangle(m_healthBarRect.x, m_healthBarRect.y, m_healthBarRect.width, m_healthBarRect.height, GRAY);
    
    // Calculate health bar width based on current health
    float healthWidth = (m_enemyHealth / 100.0f) * m_healthBarRect.width;
    
    // Draw health bar
    DrawRectangle(m_healthBarRect.x, m_healthBarRect.y, healthWidth, m_healthBarRect.height, RED);
    DrawRectangleLines(m_healthBarRect.x, m_healthBarRect.y, m_healthBarRect.width, m_healthBarRect.height, BLACK);
    
}

void Enemy::drawHurtFrame() {
    DrawTexture(m_enemyHurt, m_positionX, m_positionY, WHITE);
}

void Enemy::updateSprite(){
    m_healthBarRect.x = m_positionX; 
    m_healthBarRect.y = m_positionY - 13.0f;
    if(m_hurtFrameActive) {
        drawHurtFrame();
        m_hurtFrameActive = false; // Reset hurt frame after drawing
    }
    else{
        animateSprite();
        drawSprite();
    }
    drawHealthBar();
}
    
/*-------------------------------*/
float Enemy::getHealth() {
    return m_enemyHealth;
}  

void Enemy::setHealth(float health) {
    m_enemyHealth = health;
}

void Enemy::setEnemySpeed(float speed){
    m_enemySpeed = speed;
}

