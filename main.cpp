#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
typedef enum GameScreen { TITLE = 0, GAMEPLAY, ENDING } GameScreen;

float clamp(float value, float min, float max){
    if(value < min){
        return min;
    }
    if (value > max){
        return max;
    }
    return value;
}


int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Cat Shooter");
    
    InitAudioDevice();
    Music title_music = LoadMusicStream("assets/title.mp3");
    Music game_music = LoadMusicStream("assets/place_holder.mp3");
    PlayMusicStream(title_music);
    
    // Backgrounds
    Image image = LoadImage("assets/title_background.png");     // Loaded in CPU memory (RAM)
    Texture2D title_background = LoadTextureFromImage(image);          // Image converted to texture, GPU memory (VRAM)
    image = LoadImage("assets/gameplay_background.png");
    Texture2D gameplay_background = LoadTextureFromImage(image);

    // Cats!!
    image = LoadImage("assets/cat_01.png");
    Texture cat_01 = LoadTextureFromImage(image);
    image = LoadImage("assets/cat_02.png");
    Texture cat_02 = LoadTextureFromImage(image);
    image = LoadImage("assets/cat_03.png");
    Texture cat_03 = LoadTextureFromImage(image);
    image = LoadImage("assets/cat_04.png");
    Texture cat_04 = LoadTextureFromImage(image);
    image = LoadImage("assets/cat_05.png");
    Texture cat_05 = LoadTextureFromImage(image);
    image = LoadImage("assets/cat_06.png");
    Texture cat_06 = LoadTextureFromImage(image);
    image = LoadImage("assets/cat_07.png");
    Texture cat_07 = LoadTextureFromImage(image);
    image = LoadImage("assets/cat_08.png");
    Texture cat_08 = LoadTextureFromImage(image);
    image = LoadImage("assets/crosshair.png");
    Texture crosshair = LoadTextureFromImage(image);
    UnloadImage(image);

    // Explosion gif
    // https://www.raylib.com/examples/textures/loader.html?name=textures_gif_player
    int animFrames = 0;
    Image imScarfyAnim = LoadImageAnim("assets/explosion.gif", &animFrames);
    Texture2D texScarfyAnim = LoadTextureFromImage(imScarfyAnim);
    
    unsigned int nextFrameDataOffset = 0;
    int currentAnimFrame = 0;       
    int frameDelay = 8;             
    int frameCounter = 0;  

    GameScreen currentScreen = TITLE;
    float crossHairRotation = 0.0f;
    int previousMouseX = GetMouseX();
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    
    // Main game loop
    while (!WindowShouldClose()){   // Detect window close button or ESC key    
        BeginDrawing();
        HideCursor();
        // Switch to handle different screens
            switch (currentScreen) {
                case TITLE:
                    UpdateMusicStream(title_music); 
                    DrawTexture(title_background, 0, 0, WHITE);
                    DrawText("Cat Shooter", 20, 20, 40, BLACK);
                    DrawText("PRESS ENTER TO START", 120, 220, 20, BLACK);
                    if (IsKeyPressed(KEY_ENTER)){
                        StopMusicStream(title_music);
                        currentScreen = GAMEPLAY;
                    }
                break;
                case GAMEPLAY:
                    if (!IsMusicStreamPlaying(game_music)) {
                        PlayMusicStream(game_music);
                    }    
                    UpdateMusicStream(game_music);
                    DrawTexture(gameplay_background, 0, 0, WHITE);
                    // im sure there's a better way to center this but this is what i could find in the cheatsheet
                    DrawText(TextFormat("Cursor position is:\nX:%i Y:%i", GetMouseX(), GetMouseY()), screenWidth/2 - MeasureText(TextFormat("Ball position is:\nX:%i Y:%i", GetMouseX(), GetMouseY()),20)/2, screenHeight/2, 20, BLACK);
                    
                    DrawTextureEx(cat_01, {0, 0}, 0, 0.5, WHITE);
                    DrawTextureEx(cat_02, {100, 0}, 0, 0.5, WHITE);
                    DrawTextureEx(cat_03, {200, 0}, 0, 0.5, WHITE);
                    DrawTextureEx(cat_04, {300, 0}, 0, 0.5, WHITE);
                    DrawTextureEx(cat_05, {400, 0}, 0, 0.5, WHITE);
                    DrawTextureEx(cat_06, {500, 0}, 0, 0.5, WHITE);
                    DrawTextureEx(cat_07, {600, 0}, 0, 0.5, WHITE);
                    DrawTextureEx(cat_08, {700, 0}, 0, 0.5, WHITE);

                    
                    frameCounter++;
                    if (frameCounter >= frameDelay){
                        // Move to next frame
                        // NOTE: If final frame is reached we return to first frame
                        currentAnimFrame++;
                        if (currentAnimFrame >= animFrames) currentAnimFrame = 0;
                        // Get memory offset position for next frame data in image.data
                        nextFrameDataOffset = imScarfyAnim.width*imScarfyAnim.height*4*currentAnimFrame;
                        // Update GPU texture data with next frame image data
                        // WARNING: Data size (frame size) and pixel format must match already created texture
                        UpdateTexture(texScarfyAnim, ((unsigned char *)imScarfyAnim.data) + nextFrameDataOffset);

                        frameCounter = 0;
                    }
                    DrawTextureEx(texScarfyAnim, {0, 50}, 0, 0.25, WHITE);



                    // Determine if crosshair is going to the left or to the right
                    if (previousMouseX < GetMouseX()) {
                        crossHairRotation += 2.0f;
                    } else if (previousMouseX > GetMouseX()) {
                        crossHairRotation -= 2.0f;  
                    } else {
                        crossHairRotation = 0.0f;
                    }

                    DrawTexturePro(crosshair, {0,0, (float)crosshair.width, (float)crosshair.height},
                    {(float)GetMouseX(), (float)GetMouseY(), (float)crosshair.width/4, (float)crosshair.height/4},
                    {(float)crosshair.width/8, (float)crosshair.height/8},
                    clamp(crossHairRotation, -25, 25),
                    WHITE);
                    previousMouseX = GetMouseX(); // We update the previous position
                break;
                case ENDING:
                    //TODO Add Game Over screen
                break;                
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    UnloadMusicStream(title_music);
    CloseAudioDevice();
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}