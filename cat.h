#include <raylib.h>
#include "gameState.h"

class Cat{
    public:
        float posX;
        float posY;
        bool isExploding = false;
        Vector2 movingDiretion{0, 0};
        
        Texture catTexture;
        Texture cat_01 = LoadTexture("assets/cats/cat_01.png");
        Texture cat_02 = LoadTexture("assets/cats/cat_02.png");
        Texture cat_03 = LoadTexture("assets/cats/cat_03.png");
        Texture cat_04 = LoadTexture("assets/cats/cat_04.png");
        Texture cat_05 = LoadTexture("assets/cats/cat_05.png");
        Texture cat_06 = LoadTexture("assets/cats/cat_06.png");
        Texture cat_07 = LoadTexture("assets/cats/cat_07.png");
        Texture cat_08 = LoadTexture("assets/cats/cat_08.png");
        
        Texture2D explosionTexture = LoadTexture("assets/cats/explosion.png");

        Sound explosionSound = LoadSound("assets/cats/explosion.mp3");
        Sound shieldBounceSound = LoadSound("assets/cats/shield_bounce.mp3");

        Cat();
        void draw(float deltaTime, GameState& gameState);
        void checkForClick(Vector2 crossHairPosition);
        void getRandomCat();
        void respawn();
        void move(GameState& gameState);
        void getNewDirection();

    private:
        int frameWidth;
        int frameHeight;
        int frameCount;
        float frameSpeed;
        int currentFrame;
        float animationTimer;
        float timer;

};