#include <raylib.h>
class Crosshair{
    public:
        int previousMouseX;
        float posX;
        float posY;
        float crossHairRotation;
        Texture crosshairTexture;
        
        Crosshair(Texture crosshairTexture);
        void drawCrosshair();
        
};