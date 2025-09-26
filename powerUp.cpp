#include "raylib.h"
#include "powerUp.h"

PowerUp::PowerUp(){
    this->timer = 0;
}

void PowerUp::draw(float deltaTime, GameState& gameState, Vector2 crossHairPosition){
    if (this->visible) {
        DrawTextureEx(this->powerUpTexture, { this->posX, this->posY }, 0, 1, WHITE);
    }

    // Every 10 seconds, a power up will spawn
    this->timer += deltaTime;
    if (this->timer >= 5.0f && this->visible == false) {
        respawn();
        this->visible = true;
    }

    if (this->timer >= 1.0f && this->visible) {
        this->visible = false;
        this->timer = 0;
    }

    if (checkForClick(crossHairPosition) && this->visible) {
        switch (this->type) {
            case SHIELDTYPE:
                this->visible = false;
                this->timer = 0;
                gameState.shield = 3;
                PlaySound(this->shieldSound);
            break;

            case HEALTYPE:
                this->visible = false;
                this->timer = 0;
                gameState.health ++;
                PlaySound(this->healSound);
            break;

            case LESSCATSTYPE:
                this->visible = false;
                this->timer = 0;
                gameState.flagDespawnCat = true;
                PlaySound(this->lessCatsSound);
            break;

            case ENUMCOUNT:
                CloseWindow();
            break;
        }
    
    }


}

void PowerUp::getNewType(){
    switch (GetRandomValue(0, ENUMCOUNT-1)) {
        case 0:
            this->type = SHIELDTYPE;
            this->powerUpTexture = shieldTexture;
        break;

        case 1:
            this->type = HEALTYPE;
            this->powerUpTexture = healTexture;
        break;

        case 2:
            this->type = LESSCATSTYPE;
            this->powerUpTexture = lessCatsTexture;
        break;
    }
    
}

void PowerUp::respawn(){
    getNewType();
    this->timer = 0;
    this->posX = (float)GetRandomValue(50, (int)(700-this->powerUpTexture.width));
    this->posY = (float)GetRandomValue(50, (int)(350-this->powerUpTexture.height));
}

bool PowerUp::checkForClick(Vector2 crossHairPosition){
    if (((crossHairPosition.x <= (this->posX + (float)this->powerUpTexture.width) && crossHairPosition.x >= this->posX) &&
        (crossHairPosition.y <= (this->posY + (float)this->powerUpTexture.height) && crossHairPosition.y >= this->posY))
        && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            return true;
    }
    return false;
}

