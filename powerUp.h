#include <raylib.h>
#include "gameState.h"

class PowerUp{
    public:

        enum PowerType{
            SHIELDTYPE = 0,
            HEALTYPE,
            LESSCATSTYPE,
            SLOWTIMETYPE,
            ENUMCOUNT
        };

        PowerType type;
        float posX;
        float posY;
        bool visible = false;
        bool powerInEffect = false;

        
        Texture powerUpTexture;
        Texture shieldTexture = LoadTexture("assets/power_ups/shield.png");
        Texture healTexture = LoadTexture("assets/power_ups/heal.png");
        Texture lessCatsTexture = LoadTexture("assets/power_ups/less_cats.png");
        Texture slowTimeTexture = LoadTexture("assets/power_ups/slow_time.png");


        Sound shieldSound = LoadSound("assets/power_ups/shield.mp3");
        Sound healSound = LoadSound("assets/power_ups/heal.mp3");
        Sound lessCatsSound = LoadSound("assets/power_ups/less_cats.mp3");
        Sound slowTimeSound = LoadSound("assets/power_ups/slow_time.mp3");
        Sound normalTimeSound = LoadSound("assets/power_ups/normal_time.mp3");

        PowerUp();
        void draw(float deltaTime, GameState& gameState, Vector2 crossHairPositions);
        bool checkForClick(Vector2 crossHairPosition);
        void getNewType();
        void respawn();
    
    private:
        float timer;
};