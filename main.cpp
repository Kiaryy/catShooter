#include "raylib.h"
#include "cat.h"
#include "crosshair.h"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
typedef enum GameScreen { TITLE = 0, GAMEPLAY, ENDING } GameScreen;

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
    UnloadImage(image);

    // Cats!!
    Cat cat1{100.0f, 100.0f};
    Cat cat2{200.0f, 100.0f};
    // crosshair
    Crosshair crosshair{};

    int score = 0;

    GameScreen currentScreen = TITLE;
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    
    // Main game loop
    while (!WindowShouldClose()){   // Detect window close button or ESC key    
        float deltaTime = GetFrameTime();
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
                    DrawText(TextFormat("Score: %i", score), 680 - MeasureText(TextFormat("Ball position is:\nX:%i Y:%i", GetMouseX(), GetMouseY()),20)/2, 25, 20, BLACK);
                    
                    
                    cat1.draw(deltaTime, score);
                    cat2.draw(deltaTime, score);
                    cat1.checkForClick(GetMousePosition());
                    cat2.checkForClick(GetMousePosition());

                    
                    crosshair.drawCrosshair();

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