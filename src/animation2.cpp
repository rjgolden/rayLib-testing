#include "animation2.h"

/*-------------------------------*/
Animation::Animation(const char* filePath, uint8_t frameCount, float positionX, float positionY){

    // Load textures
    m_animationTextures[0] = LoadTexture(filePath);

    // Rectangles 
    m_animationRect = { 0.0f, 0.0f, (float)m_animationTextures[0].width / 6.0f, (float)m_animationTextures[0].height }; 
    m_hitboxRect = { 0.0f, 0.0f, (float)m_animationTextures[0].width / 6.0f, (float)m_animationTextures[0].height };

    // frame stuff
    m_currentFrame = 0; // Starting frame
    m_frameCount = frameCount; // Number of frames in the idle animation
    m_runningTime = 0.0f; 
    m_updateTime = 1.0f / 12.0f;
    m_scale = 1.0f; 

    // position and speed
    m_positionX = positionX; 
    m_positionY = positionY; 

    std::cout << "Animation created\n";
}

Animation::Animation() {};

Animation::~Animation(){
    UnloadTexture(m_animationTextures[0]);
    std::cout << "Animation Destroyed, texture(s) succesfully unloaded.\n";
}

/*-------------------------------*/
void Animation::animateSprite(){
    float deltaTime = GetFrameTime();
    m_runningTime += deltaTime;
    if (m_runningTime >= m_updateTime){
        m_runningTime = 0.0f;
        m_animationRect.x = (float)m_currentFrame * m_animationRect.width;
        m_currentFrame++;
        //if (m_currentFrame > m_frameCount) m_currentFrame = rand() % m_frameCount; // for random  
        if (m_currentFrame > m_frameCount) m_currentFrame = 0; 
    }
}

void Animation::drawSprite(){
    DrawTexturePro(m_animationTextures[0], m_animationRect, {(float)m_positionX, (float)m_positionY, 32.0f, 32.0f}, {0.0f, 0.0f}, 0.0f, WHITE);
}

void Animation::drawHitbox(){
    DrawRectangleLines(m_positionX, m_positionY, m_hitboxRect.width, m_hitboxRect.height, RED);
}

void Animation::drawRectbox(){
    DrawRectangleLines(m_positionX, m_positionY, m_animationRect.width, m_animationRect.height, GREEN);
}

void Animation::updateSprite(){
    animateSprite();
    drawSprite();
    //drawHitbox();
    drawRectbox();
}

/*-------------GETTERS------------*/
float Animation::getPositionX() { 
    return m_positionX; 
}

float Animation::getPositionY() { 
    return m_positionY; 
}

float Animation::getWidth() { 
    return m_hitboxRect.width; 
}

float Animation::getHeight() { 
    return m_hitboxRect.height; 
}

Rectangle Animation::getHitboxRect() { 
    return {m_positionX, m_positionY, m_hitboxRect.width, m_hitboxRect.height}; 
}

/*-------------SETTERS------------*/
void Animation::setPosition(float x, float y){
    m_positionX = x;
    m_positionY = y;
}

void Animation::setScale(float scale){
    m_scale = scale;
}