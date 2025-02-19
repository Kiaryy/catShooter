#include <raylib.h>

class Cat{
    public:
    float posX;
    float posY;
    Texture catTexture;
    Texture2D explosionTexture;
    Sound explosionSound;
    bool isExploding = false;

    Texture cat_01 = LoadTexture("assets/cat_01.png");
    Texture cat_02  = LoadTexture("assets/cat_02.png");
    Texture cat_03  = LoadTexture("assets/cat_03.png");
    Texture cat_04  = LoadTexture("assets/cat_04.png");
    Texture cat_05  = LoadTexture("assets/cat_05.png");
    Texture cat_06  = LoadTexture("assets/cat_06.png");
    Texture cat_07  = LoadTexture("assets/cat_07.png");
    Texture cat_08 = LoadTexture("assets/cat_08.png");



    Cat(float posX, float posY, Texture2D explosionTexture);
    void draw(float deltaTime);
    void checkForClick(Vector2 crossHairPosition);
    void getRandomCat();
    private:
        int frameWidth;
        int frameHeight;
        int frameCount;
        float frameSpeed;
        int currentFrame;
        float timer;

};