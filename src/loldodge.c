#include "player.h"
#include "enemy.h"
#include "sprite.h"
#include <raylib.h>

//----------------------------------------------------------------------------------
// Defines
//----------------------------------------------------------------------------------
#define PLAYER_SPEED 270.0f
#define ENEMY_SPEED 170.0f

#define MAX_ENEMIES 100
#define MAX_SHOTS 100

//----------------------------------------------------------------------------------
// Global Variables
//----------------------------------------------------------------------------------
static int screenWidth = 1600;
static int screenHeight = 900;
static int framerate = 240;

static bool gameOver = false;

static Player player = {0};
static Texture2D playerTexture;

static Enemy enemy[MAX_ENEMIES] = {0};
static Texture2D enemyTexture;
static Texture2D bgTexture;

float spawnTimer = 0.0f;
float spawnInterval = 5.0f;

//------------------------------------------------------------------------------------
// Game Functions
//------------------------------------------------------------------------------------
static void GameInit(void);   // Initialize game
static void GameUpdate(void); // Update game (one frame)
static void GameDraw(void);   // Draw game (one frame)
static void GameUnload(void); // Unload game

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "loldodge");
    SetTargetFPS(framerate);

    GameInit();
    while (!WindowShouldClose()) {
        GameUpdate();
        GameDraw();
    }

    GameUnload();
    CloseWindow();
    return 0;
}

void GameInit() {
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();

    Image bgImage = LoadImage("./assets/map.png");
    bgTexture = LoadTextureFromImage(bgImage);
    UnloadImage(bgImage);

    playerTexture = LoadTexture("./assets/knight_blue.png");
    PlayerInit(&player, playerTexture,
               (Vector2){screenWidth/2.0f, screenHeight/2.0f},
               PLAYER_SPEED);

    enemyTexture = LoadTexture("./assets/knight.png");
    for (int i = 0; i < MAX_ENEMIES; i++) {
        EnemyInit(&enemy[i], enemyTexture, ENEMY_SPEED, (Sprite*)&player);
    }
}

void SpawnEnemies() {
    spawnTimer += GetFrameTime();
    if (spawnTimer < spawnInterval)
        return;
    spawnTimer = 0.0f;

    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!enemy[i].active) {
            EnemySpawn(&enemy[i]);
            break;
        }
    }
}

void GameUpdate() {
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();

    SpriteUpdate((Sprite*)&player);
    SpriteMove((Sprite*)&player);

    SpawnEnemies();
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemy[i].active) {
            SpriteUpdate((Sprite*)&enemy[i]);
            SpriteMove((Sprite*)&enemy[i]);
        }
    }
}

void GameDraw() {
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawTexturePro(
        bgTexture,
        (Rectangle){0, 0, (float)bgTexture.width, (float)bgTexture.height},
        (Rectangle){0, 0, (float)screenWidth, (float)screenHeight},
        (Vector2){0, 0}, 0.0f, RAYWHITE);

    SpriteDraw((Sprite*)&player);
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemy[i].active)
            SpriteDraw((Sprite*)&enemy[i]);
    }

    EndDrawing();
}

void GameUnload() {
    UnloadTexture(playerTexture);
    UnloadTexture(enemyTexture);
    UnloadTexture(bgTexture);
}
