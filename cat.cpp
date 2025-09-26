#include "cat.h"
#include <raylib.h>

Cat::Cat(){
    getRandomCat();
    respawn();
    SetSoundVolume(this->explosionSound, 0.10f);
    this->frameWidth = this->explosionTexture.width / 16; // Asuming 16 frames
    this->frameHeight = this->explosionTexture.height;
    this->frameCount = 16;  // Number of frames
    this->frameSpeed = 0.025f; // Speed (seconds per frame)
    this->currentFrame = 0; // Current frame
    this->animationTimer = 0; // Animation Timer
}

void Cat::getRandomCat(){
    switch (GetRandomValue(1, 8)) {
        case 1:
            this->catTexture = cat_01;
        break;
        case 2:
            this->catTexture = cat_02;
        break;
        case 3:
            this->catTexture = cat_03;
        break;
        case 4:
            this->catTexture = cat_04;
        break;
        case 5:
            this->catTexture = cat_05;
        break;
        case 6:
            this->catTexture = cat_06;
        break;
        case 7:
            this->catTexture = cat_07;
        break;
        case 8:
            this->catTexture = cat_08;
        break;
        
    }
}


void Cat::draw(float deltaTime, GameState& gameState) {
    DrawTextureEx(this->catTexture, { this->posX, this->posY }, 0, 1, WHITE);
    
    // Change direction every second
    this->timer += deltaTime;
    if (this->timer >= 1.0f) {
        getNewDirection();
    }

    if (gameState.shield > 0) {
        // Handle collision with shield
        if ((this->posX + (float)this->catTexture.width > 800) || this->posX < 0) {
            PlaySound(this->shieldBounceSound);
            gameState.shield -= 1;
            respawn();
            getRandomCat();
            getNewDirection();
        }
    
        if ((this->posY + (float)this->catTexture.height > 450) || this->posY < 0) {
            PlaySound(this->shieldBounceSound);
            gameState.shield -= 1;
            respawn();
            getRandomCat();
            getNewDirection();
        } 
    } else {
        // Handle collision with border
        if (this->posX > 800 || (this->posX + (float)this->catTexture.width < 0)) {
            gameState.health -= 1;
            respawn();
            getRandomCat();
            getNewDirection();
        }
    
        if (this->posY > 450 || (this->posY + (float)this->catTexture.height < 0)) {
            gameState.health -= 1;
            respawn();
            getRandomCat();
            getNewDirection();
        }        
    }
    


    // Handle explosion
    if (this->isExploding) {
        // Only play the sound effect in the first frame
        if (this->currentFrame == 0 && this->animationTimer == 0) {
            gameState.score += 100;
            PlaySound(this->explosionSound);
        }
    
        this->animationTimer += deltaTime;
    
        // Update frame based on time
        if (this->animationTimer >= this->frameSpeed) {
            this->animationTimer = 0;
            this->currentFrame = (this->currentFrame + 1) % this->frameCount;
        }
    
        Rectangle sourceRect = {
            (float)this->currentFrame * this->frameWidth, 0, // X position in spritesheet
            (float)this->frameWidth, (float)this->frameHeight // Frame size
        };
    
        Rectangle destRect = { this->posX, this->posY, (float)this->frameWidth, (float)this->frameHeight };
        DrawTexturePro(this->explosionTexture, sourceRect, destRect, { 0, 0 }, 0, WHITE);
        if (currentFrame == 15) {
            this->isExploding = false;
            currentFrame = 0;
            respawn();
            getRandomCat();
        }
    }
}

void Cat::checkForClick(Vector2 crossHairPosition){
    // Nuclear mess of an if to read but this aint python lil bro get used to shit awful code
    if (((crossHairPosition.x <= (this->posX + (float)this->catTexture.width) && crossHairPosition.x >= this->posX) &&
        (crossHairPosition.y <= (this->posY + (float)this->catTexture.height) && crossHairPosition.y >= this->posY))
        && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            this->isExploding = true;    
    }
}

void Cat::respawn(){
    getNewDirection();
    this->posX = (float)GetRandomValue(50, (int)(700-this->catTexture.width));
    this->posY = (float)GetRandomValue(50, (int)(350-this->catTexture.height));
}

void Cat::getNewDirection(){
    this->timer = 0;
    this->movingDiretion.x =(float)GetRandomValue(-2, 2);
    this->movingDiretion.y =(float)GetRandomValue(-2, 2);
}

void Cat::move(){
    if(!this->isExploding){
        this->posX += this->movingDiretion.x;
        this->posY += this->movingDiretion.y;
    }
}