#include "raylib.h"
#include "cat.h"
#include "crosshair.h"
#include <vector>
#include "powerUp.h"

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
    Music gameover_music = LoadMusicStream("assets/gameover.mp3");
    SetMusicVolume(gameover_music, 0.5f);
    // Backgrounds
    Image image = LoadImage("assets/title_background.png");     // Loaded in CPU memory (RAM)
    Texture2D title_background = LoadTextureFromImage(image);          // Image converted to texture, GPU memory (VRAM)
    image = LoadImage("assets/gameplay_background.png");
    Texture2D gameplay_background = LoadTextureFromImage(image);
    image = LoadImage("assets/gameover_background.png");
    Texture2D gameover_background = LoadTextureFromImage(image);
    UnloadImage(image);

    // Cats!!
    std::vector<Cat> cats{};
    // crosshair
    Crosshair crosshair{};
    PowerUp powerUp {};
    GameState gameState;


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
                    // Music stuff
                    if (!IsMusicStreamPlaying(title_music)) {
                        PlayMusicStream(title_music);
                    }   
                    UpdateMusicStream(title_music); 
                    // We set (or reset) game data
                    if (gameState.resetFlag){
                        cats.clear();
                        cats.push_back({});
                        cats.push_back({});
                        
                        gameState.health = 3;
                        gameState.score = 0;
                        
                        gameState.resetFlag = false;
                    }

                    DrawTexture(title_background, 0, 0, WHITE);
                    DrawText("Cat Shooter", 20, 20, 40, BLACK);
                    DrawText("PRESS ENTER TO START", 120, 220, 20, BLACK);
                    if (IsKeyPressed(KEY_ENTER)){
                        StopMusicStream(title_music);
                        currentScreen = GAMEPLAY;
                        gameState.resetFlag = true;
                    }
                break;
                case GAMEPLAY:
                    if (!IsMusicStreamPlaying(game_music)) {
                        PlayMusicStream(game_music);
                    }    
                    UpdateMusicStream(game_music);

                    DrawTexture(gameplay_background, 0, 0, WHITE);
                    // im sure there's a better way to center this but this is what i could find in the cheatsheet
                    // DrawText(TextFormat("Cursor position is:\nX:%i Y:%i", GetMouseX(), GetMouseY()), screenWidth/2 - MeasureText(TextFormat("Ball position is:\nX:%i Y:%i", GetMouseX(), GetMouseY()),20)/2, screenHeight/2, 20, BLACK);
                    DrawText(TextFormat("Score: %i", gameState.score), 700 - MeasureText(TextFormat("Ball position is:\nX:%i Y:%i", GetMouseX(), GetMouseY()),20)/2, 25, 20, BLACK);
                    DrawText(TextFormat("Health: %i", gameState.health), 100 - MeasureText(TextFormat("Ball position is:\nX:%i Y:%i", GetMouseX(), GetMouseY()),20)/2, 25, 20, BLACK);

                    powerUp.draw(deltaTime, gameState, GetMousePosition());

                    // Shield visuals

                    if (gameState.shield == 3) {
                        DrawLineEx({1,1}, {799, 1}, 3.0f, GREEN);
                        DrawLineEx({1,1}, {1, 449}, 3.0f, GREEN);
                        DrawLineEx({799,449}, {799, 1}, 3.0f, GREEN);
                        DrawLineEx({799,449}, {1, 449}, 3.0f, GREEN);
                    }
                    
                    if (gameState.shield == 2) {
                        DrawLineEx({1,1}, {799, 1}, 3.0f, YELLOW);
                        DrawLineEx({1,1}, {1, 449}, 3.0f, YELLOW);
                        DrawLineEx({799,449}, {799, 1}, 3.0f, YELLOW);
                        DrawLineEx({799,449}, {1, 449}, 3.0f, YELLOW);
                    }

                    if (gameState.shield == 1) {
                        DrawLineEx({1,1}, {799, 1}, 3.0f, RED);
                        DrawLineEx({1,1}, {1, 449}, 3.0f, RED);
                        DrawLineEx({799,449}, {799, 1}, 3.0f, RED);
                        DrawLineEx({799,449}, {1, 449}, 3.0f, RED);
                    }

                    
                    
                    for (Cat& cat : cats) {
                        cat.draw(deltaTime, gameState);
                        cat.checkForClick(GetMousePosition());
                        cat.move(gameState);
                    }
                    
                    if (gameState.flagDespawnCat) {
                        if (!cats.empty() && cats.size() != 1) {
                            cats.pop_back();
                        }
                    
                        gameState.flagDespawnCat = false;
                    }
                    

                    if(gameState.flagSpawnNewCat && gameState.score % 1000 == 0 && gameState.score !=0){
                        gameState.flagSpawnNewCat = false;
                        cats.push_back({});
                    }

                    if (gameState.score % 1000) {
                        gameState.flagSpawnNewCat = true;
                    }
                    
                    crosshair.drawCrosshair();

                    if(gameState.health <= 0){
                        currentScreen = ENDING;
                    }
                break;
                case ENDING:
                    if (!IsMusicStreamPlaying(gameover_music)) {
                        PlayMusicStream(gameover_music);
                    }
                    if (gameState.highScore < gameState.score){
                        gameState.highScore = gameState.score;
                    }
                    UpdateMusicStream(gameover_music);
                    DrawTexture(gameover_background, 0, 0, WHITE);
                    DrawText("Game Over!", 300, 150, 40, BLACK);
                    DrawText(TextFormat("PRESS ENTER TO TRY AGAIN\n\tHigh Score: %i", gameState.highScore), 250, 220, 20, BLACK);
                    if (IsKeyPressed(KEY_ENTER)){
                        StopMusicStream(gameover_music);
                        currentScreen = TITLE;
                    }
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