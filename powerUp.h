#include <raylib.h>
#include "gameState.h"

class PowerUp{
    public:

        enum PowerType{
            SHIELDTYPE = 0,
            HEALTYPE,
            LESSCATSTYPE,
            ENUMCOUNT
        };

        PowerType type;
        float posX;
        float posY;
        bool visible = false;

        
        Texture powerUpTexture;
        Texture shieldTexture = LoadTexture("assets/shield.png");
        Texture healTexture = LoadTexture("assets/heal.png");
        Texture lessCatsTexture = LoadTexture("assets/less_cats.png");


        Sound shieldSound = LoadSound("assets/shield.mp3");
        Sound healSound = LoadSound("assets/heal.mp3");
        Sound lessCatsSound = LoadSound("assets/less_cats.mp3");

        PowerUp();
        void draw(float deltaTime, GameState& gameState, Vector2 crossHairPositions);
        bool checkForClick(Vector2 crossHairPosition);
        void getNewType();
        void respawn();
    
    private:
        float timer;
};