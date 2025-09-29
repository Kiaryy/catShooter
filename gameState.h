#pragma once
struct GameState{
    int score;
    int highScore = 0;
    int health;
    int shield = 0; // Shield ranges from 3 to 0, this means it can take 3 hits before its "broken"
    float catSpeedMult = 1;

    bool resetFlag = true;
    bool flagSpawnNewCat = true;
    bool flagDespawnCat = false;
};