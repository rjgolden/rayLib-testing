#include "player2.h"

/*-------------------------------*/
Player::Player() {
    
    // vector Derived from animation class
    m_animationTextures[0] = LoadTexture("src/resources/Animations/eyeball-Idle.png"); 
    m_animationTextures[1] = LoadTexture("src/resources/Animations/eyeballMoveLeft.png");
    m_animationTextures[2] = LoadTexture("src/resources/Animations/eyeballMoveRight.png");
    m_animationTextures[3] = LoadTexture("src/resources/Animations/eyeballMoveUp.png");
    m_currentTexture = &m_animationTextures[0]; // default is idle
    
    m_frameCount = 8;

    // Rectangles - Derived from animation class
    m_animationRect = { 0.0f, 0.0f, static_cast<float>(m_animationTextures[0].width) / static_cast<float>(m_frameCount), static_cast<float>(m_animationTextures[0].height) }; 
    m_hitboxRect = { 0.0f, 0.0f, static_cast<float>(m_animationTextures[0].width) / static_cast<float>(m_frameCount), static_cast<float>(m_animationTextures[0].height) };

    // position and speed, Variables derived from animation class
    m_positionX = static_cast<float>(config::halfScreenWidth);
    m_positionY = static_cast<float>(config::halfScreenHeight); 

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
    DrawTexturePro(*m_currentTexture, m_animationRect, {static_cast<float>(m_positionX), static_cast<float>(m_positionY), static_cast<float>(m_animationTextures[0].width) / static_cast<float>(m_frameCount), static_cast<float>(m_animationTextures[0].height)}, {0.0f, 0.0f}, m_rotation, WHITE);
}

void Player::drawHitbox() {
    DrawEllipseLines(m_positionX + 16.5f, m_positionY + 32.0f, 8.0f, 12.0f, RED); 
}

void Player::setState(uint8_t newState){

    m_updateTime = 1.0f / m_animationTime;

    if (newState != m_currentState) {  
        m_currentState = newState;
        m_lastDirection = newState;

        switch(newState) {
            case LEFT: m_currentTexture = &m_animationTextures[1]; m_animationTime = 12.0f; break;  // left
            case RIGHT: m_currentTexture = &m_animationTextures[2]; m_animationTime = 12.0f; break;  // right
            case UP: m_currentTexture = &m_animationTextures[3]; m_animationTime = 12.0f; break;  // up
            case DOWN: m_currentTexture = &m_animationTextures[0]; m_animationTime = 12.0f; break;  // down
            default: m_currentTexture = &m_animationTextures[0]; m_animationTime = 6.0f; break; // idle 
        }
    }

}

void Player::handleKeyboardMovement(){
    bool wasIdle = m_idle; 
    //m_direction = 0; uncomment if idle default is wanted
    
    //---------------//
    if (IsKeyDown(KEY_A)) {
        m_idle = false;
        m_direction = LEFT; 
        m_positionX -= m_playerSpeed;
    }
    else if (IsKeyDown(KEY_D)){ 
        m_idle = false;
        m_direction = RIGHT;
        m_positionX += m_playerSpeed;
    }

    if (IsKeyDown(KEY_W)){ 
        m_idle = false;
        m_direction = UP;
        m_positionY -= m_playerSpeed;
    }
    else if (IsKeyDown(KEY_S)){ 
        m_idle = false;
        m_direction = IDLE;
        m_positionY += m_playerSpeed;
    }

    // Reset animation if state changed
    if (wasIdle != m_idle) {
        m_currentFrame = 0;
        m_runningTime = 0.0f;
    }
    
}

void Player::handleControllerMovement(){
    
    m_axisX = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X);
    m_axisY = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y);

    if (IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) {
        m_idle = false;
        m_direction = LEFT; 
        m_positionX -= m_playerSpeed;
    }
    else if (IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) {
            m_idle = false;
            m_direction = RIGHT;
            m_positionX += m_playerSpeed;
    }
    if (IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_UP)) {
        m_idle = false;
        m_direction = UP;
        m_positionY -= m_playerSpeed;
    }
    else if (IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN)) {
        m_idle = false;
        m_direction = IDLE;
        m_positionY += m_playerSpeed;
    }

    //right controller movement
    if (std::fabs(m_axisX) > 0.1f) {
        m_idle = false;
        m_positionX += m_axisX * m_playerSpeed;
            if(m_axisX > 0.3f){
            m_direction = RIGHT;
        }
        else if(m_axisX < -0.3f) {
            m_direction = LEFT;
        }
        
    }
    if (std::fabs(m_axisY) > 0.1f) {
        m_idle = false;
        m_positionY  += m_axisY * m_playerSpeed;
        if(m_axisY > 0.3f){
            m_direction = IDLE;
        }
        else if(m_axisY < -0.3f) {
            m_direction = UP;
        }
    }
}

void Player::handleKeyboardDash(){

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

void Player::handleControllerDash(){

    if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_TRIGGER_2) && !m_isDashing){
        m_isDashing = true;
        m_dashTimer = m_dashTime;
    }

    float deltaTime = GetFrameTime();

    if (m_isDashing) {

        float move = m_dashSpeed * deltaTime;

        // UP & DIAGONAL UPs
        if(IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_UP)) m_positionY -= move;
        else if(IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_UP) && IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) { m_positionY -= move; m_positionX += move; }
        else if(IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_UP) && IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) { m_positionY -= move; m_positionX -= move; }

        // DOWN & DIAGONAL DOWNS
        if(IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN)) m_positionY += move;
        else if(IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN) && IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) { m_positionY += move; m_positionX += move; }
        else if(IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN) && IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) { m_positionY += move; m_positionX -= move; }

        // LEFT & RIGHT
        if(IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) m_positionX -= move;
        if(IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) m_positionX += move;

        // right controller movement
        if (std::fabs(m_axisX) > 0.1f) {
            if(m_axisX > 0.3f){
                m_positionX  +=  move;
            }
            else if(m_axisX < -0.3f) {
                m_positionX  -= move;
            }
            
        }
        if (std::fabs(m_axisY) > 0.1f) {
            if(m_axisY > 0.3f){
                m_positionY  +=  move;
            }
            else if(m_axisY < -0.3f) {
                m_positionY  -= move;
            }
        }


        m_dashTimer -= deltaTime;
        if (m_dashTimer <= 0.0f) {
            m_isDashing = false;
        }
    }

    m_hitboxRect.x = m_positionX; 
    m_hitboxRect.y = m_positionY;
}

void Player::handleKeyboardAttack() {

    static Music m_attackSound = LoadMusicStream("src/resources/Sounds/laser.wav");
    static Animation beam("src/resources/Animations/defaultBeam.png", 8, 0.0f, 0.0f, false);
    m_attackSound.looping = true;
    beam.setPosition({m_positionX, m_positionY});
    beam.setRotation(0.0f);
    //many mahgic numbers here  - will fix in future

    if(IsKeyDown(KEY_LEFT)){
        m_idle = false;
        m_direction = LEFT; 
        beam.setPosition(Vector2({m_positionX-120.0f, m_positionY + 16.0f}));
        beam.updateSprite();
        if (!IsMusicStreamPlaying(m_attackSound)) {
            PlayMusicStream(m_attackSound);
        }
        UpdateMusicStream(m_attackSound); 
    }
    else if(IsKeyDown(KEY_RIGHT)){
        m_idle = false;
        m_direction = RIGHT;
       
        beam.setPosition(Vector2({m_positionX + 24.0f, m_positionY + 16.0f}));
        beam.updateSprite();
        if (!IsMusicStreamPlaying(m_attackSound)) {
            PlayMusicStream(m_attackSound);
        }
        UpdateMusicStream(m_attackSound); 
    }
    else if(IsKeyDown(KEY_UP)){
        m_idle = false;
        m_direction = UP; 
        
        beam.setPosition(Vector2({m_positionX, m_positionY + 16.0f}));
        beam.setRotation(270.0f);
        beam.updateSprite();
        if (!IsMusicStreamPlaying(m_attackSound)) {
            PlayMusicStream(m_attackSound);
        }
        UpdateMusicStream(m_attackSound); 
    }
    else if(IsKeyDown(KEY_DOWN)){
        m_idle = false;
        m_direction = DOWN; 
       
        beam.setPosition(Vector2({m_positionX + 32.0f, m_positionY + 32.0f}));
        beam.setRotation(90.0f);
        drawSprite(); 
        beam.updateSprite();
        if (!IsMusicStreamPlaying(m_attackSound)) {
            PlayMusicStream(m_attackSound);
        }
        UpdateMusicStream(m_attackSound); 
    }
    else {
        if (IsMusicStreamPlaying(m_attackSound)) {
            PauseMusicStream(m_attackSound);
        }
    }
  

}

void Player::handleControllerAttack() {
    
    static Music m_attackSound = LoadMusicStream("src/resources/Sounds/laser.wav");
    m_attackSound.looping = true;

    if(IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT)){
        m_idle = false;
        m_direction = LEFT; 
       
        if (!IsMusicStreamPlaying(m_attackSound)) {
            PlayMusicStream(m_attackSound);
        }
        UpdateMusicStream(m_attackSound); 
    }
    else if(IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)){
        m_idle = false;
        m_direction = RIGHT;
       
        if (!IsMusicStreamPlaying(m_attackSound)) {
            PlayMusicStream(m_attackSound);
        }
        UpdateMusicStream(m_attackSound); 
    }
    else if(IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_UP)){
        m_idle = false;
        m_direction = UP; 
       
        if (!IsMusicStreamPlaying(m_attackSound)) {
            PlayMusicStream(m_attackSound);
        }
        UpdateMusicStream(m_attackSound); 
    }
    else if(IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)){
        m_idle = false;
        m_direction = IDLE; 
       
        if (!IsMusicStreamPlaying(m_attackSound)) {
            PlayMusicStream(m_attackSound);
        }
        UpdateMusicStream(m_attackSound); 
    }
    else {
        if (IsMusicStreamPlaying(m_attackSound)) {
            PauseMusicStream(m_attackSound);
        }
    }

    //right stick movement
    m_axisXR = GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_X);
    m_axisYR = GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_Y);

    if (std::fabs(m_axisXR) > 0.1f) {
        if(m_axisXR > 0.3f){
            m_idle = false;
            m_direction = RIGHT;
           
            if (!IsMusicStreamPlaying(m_attackSound)) {
                PlayMusicStream(m_attackSound);
            }
            UpdateMusicStream(m_attackSound); 
        }
        else if(m_axisXR < -0.3f) {
            m_idle = false;
            m_direction = LEFT; 
        
            if (!IsMusicStreamPlaying(m_attackSound)) {
                PlayMusicStream(m_attackSound);
            }
            UpdateMusicStream(m_attackSound); 
        }   
    }
    if (std::fabs(m_axisYR) > 0.1f) {
        if(m_axisYR > 0.3f){
            m_idle = false;
            m_direction = IDLE; 
          
            if (!IsMusicStreamPlaying(m_attackSound)) {
                PlayMusicStream(m_attackSound);
            }
            UpdateMusicStream(m_attackSound); 
        }
        else if(m_axisYR < -0.3f) {
            m_idle = false;
            m_direction = UP; 
           
            if (!IsMusicStreamPlaying(m_attackSound)) {
                PlayMusicStream(m_attackSound);
            }
            UpdateMusicStream(m_attackSound);
        }
    }
    
   
}

void Player::updateSprite() {

    handleKeyboardMovement();
    handleKeyboardDash();
    handleKeyboardAttack();
    if(IsGamepadAvailable(0)){
        handleControllerMovement();
        handleControllerDash();
        handleControllerAttack();
    }
    setState(m_direction);  
    animateSprite();
    if(m_direction == DOWN){
        drawHitbox();
    }
    else{
        drawSprite();
        drawHitbox();
    }

}

/*-------------GETTERS------------*/
float Player::getPlayerSpeed(){
    return m_playerSpeed;
}
