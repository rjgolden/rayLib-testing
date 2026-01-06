#include "animation2.h"

/*-------------------------------*/
Animation::Animation(const char* filePath, uint8_t frameCount, float positionX, float positionY, bool random){

    // Load textures
    m_animationTextures[0] = LoadTexture(filePath);

    // Rectangles 
    m_animationRect = { 0.0f, 0.0f, static_cast<float>(m_animationTextures[0].width) / static_cast<float>(frameCount), static_cast<float>(m_animationTextures[0].height) }; 
    m_hitboxRect = { 0.0f, 0.0f, static_cast<float>(m_animationTextures[0].width) / static_cast<float>(frameCount), static_cast<float>(m_animationTextures[0].height) };

    // frame stuff
    m_frameCount = frameCount; // Number of frames in the idle animation
    m_random = random;
    
    // position and speed
    m_positionX = positionX; 
    m_positionY = positionY; 

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
        m_animationRect.x = static_cast<float>(m_currentFrame) * m_animationRect.width;
        m_currentFrame++;
        //if (m_currentFrame > m_frameCount) m_currentFrame = rand() % m_frameCount; // for random  
        if (m_currentFrame > m_frameCount) m_currentFrame = 0; 
    }
}

void Animation::animateSpriteRandom(){
    float deltaTime = GetFrameTime();
    m_runningTime += deltaTime;
    if (m_runningTime >= m_updateTime){
        m_runningTime = 0.0f;
        m_animationRect.x = static_cast<float>(m_currentFrame) * m_animationRect.width;
        m_currentFrame++;
        if (m_currentFrame > m_frameCount) m_currentFrame = rand() % m_frameCount; // for random  
    }
}

void Animation::drawSprite(){
    DrawTexturePro(m_animationTextures[0], m_animationRect, {static_cast<float>(m_positionX), static_cast<float>(m_positionY), static_cast<float>(m_animationTextures[0].width) / static_cast<float>(m_frameCount), static_cast<float>(m_animationTextures[0].height)}, {0.0f, 0.0f}, m_rotation, WHITE);
}

void Animation::drawHitbox(){
    DrawRectangleLines(m_positionX, m_positionY, m_hitboxRect.width, m_hitboxRect.height, RED);
}

void Animation::updateSprite(){
    if(m_random) animateSpriteRandom();
    else animateSprite();
    drawSprite();
    //drawRectbox();
    drawHitbox();
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

Vector2 Animation::getPosition() { 
    return Vector2{m_positionX, m_positionY};
}

Rectangle Animation::getHitboxRect() { 
    return {m_positionX, m_positionY, m_hitboxRect.width, m_hitboxRect.height}; 
}

/*-------------SETTERS------------*/
void Animation::setPosition(Vector2 position){
    m_positionX = position.x;
    m_positionY = position.y;
}

void Animation::setRotation(float rotation){
    m_rotation = rotation;
}