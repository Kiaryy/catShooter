#include "cat.h"
#include <raylib.h>

Cat::Cat(float posX, float posY, Texture catTexture, Texture2D explosionTexture){
    this->posX = posX;
    this->posY = posY;
    this->catTexture = catTexture;
    this->explosionSound = LoadSound("assets/explosion.mp3");
    SetSoundVolume(explosionSound, 0.25f);
    this->explosionTexture = explosionTexture;

    this->frameWidth = this->explosionTexture.width / 16; // Asuming 16 frames
    this->frameHeight = this->explosionTexture.height;
    this->frameCount = 16;  // Number of frames
    this->frameSpeed = 0.1f; // Speed (seconds per frame)
    this->currentFrame = 0; // Current frame
    this->timer = 0; // Timer
}

void Cat::draw(float deltaTime) {
    DrawTextureEx(this->catTexture, { this->posX, this->posY }, 0, 0.5, WHITE);
    if (this->isExploding) {
        // Only play the sound effect in the first frame
        if (this->currentFrame == 0 && this->timer == 0) {
            PlaySound(this->explosionSound);
        }
    
        this->timer += deltaTime;
    
        // Update frame based on time
        if (this->timer >= this->frameSpeed) {
            this->timer = 0;
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
        }
    }
}


