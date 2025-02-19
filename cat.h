#include <raylib.h>

class Cat{
    public:
    float posX;
    float posY;
    Texture catTexture;
    Texture2D explosionTexture;
    Sound explosionSound;
    bool isExploding = false;

    Cat(float posX, float posY, Texture catTexture, Texture2D explosionTexture);
    void draw(float deltaTime);
    void checkForClick(Vector2 crossHairPosition);

    private:
        int frameWidth;
        int frameHeight;
        int frameCount;
        float frameSpeed;
        int currentFrame;
        float timer;

};