#include "crosshair.h"
#include "utils.h"
#include <raylib.h>

Crosshair::Crosshair(){
}

void Crosshair::drawCrosshair(){
    // Determine if crosshair is going to the left or to the right
    if (previousMouseX < GetMouseX()) {
        crossHairRotation += 2.0f;
    } else if (previousMouseX > GetMouseX()) {
        crossHairRotation -= 2.0f;  
    } else {
        crossHairRotation = 0.0f;
    }

    DrawTexturePro(this->crosshairTexture, {0,0, (float)this->crosshairTexture.width, (float)this->crosshairTexture.height},
    {(float)GetMouseX(), (float)GetMouseY(), (float)this->crosshairTexture.width/4, (float)this->crosshairTexture.height/4},
    {(float)this->crosshairTexture.width/8, (float)this->crosshairTexture.height/8},
    clamp(this->crossHairRotation, -25.0f, 25.0f),
    WHITE);
    // This is a cool one, so the crosshair png is too big so we're only using 25% of its original size
    // So we divide the og size by 4
    // But then we need center point of the new rect to rotate it accurately
    // So we divide the og size by 8
    // So now you ask: Wouldn't it be easier to just shrink the png?
    // My response: nuh huh

    previousMouseX = GetMouseX(); // We update the previous position
}