#include <raylib.h>
class Crosshair{
    public:
        int previousMouseX;
        float posX;
        float posY;
        float crossHairRotation;
        Texture crosshairTexture = LoadTexture("assets/crosshair.png");
        
        Crosshair();
        void drawCrosshair();
        
};