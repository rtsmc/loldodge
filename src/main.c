#include "player.h"
#include "sprite.h"
#include <raylib.h>

//----------------------------------------------------------------------------------
// Defines
//----------------------------------------------------------------------------------
#define PLAYER_SPEED 300.0f

#define MAX_SPRITES 100

//----------------------------------------------------------------------------------
// Global Variables
//----------------------------------------------------------------------------------
static int screenWidth = 1600;
static int screenHeight = 900;
static int framerate = 240;

static bool gameOver = false;

static Player player = {0};
static Texture2D playerTexture;

static Sprite *sprites[MAX_SPRITES] = {0};
static int spriteCount;
static Texture2D bgTexture;

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

    playerTexture = LoadTexture("./assets/knight.png");
    PlayerInit(&player, playerTexture,
               (Vector2){screenWidth/2.0f, screenHeight/2.0f},
               PLAYER_SPEED);
    sprites[spriteCount++] = (Sprite *)&player;
}

void GameUpdate() {
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();

    for (int i = 0; i < spriteCount; i++)
        SpriteUpdate(sprites[i]);
}

void GameDraw() {
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawTexturePro(
        bgTexture,
        (Rectangle){0, 0, (float)bgTexture.width, (float)bgTexture.height},
        (Rectangle){0, 0, (float)screenWidth, (float)screenHeight},
        (Vector2){0, 0}, 0.0f, RAYWHITE);

    for (int i = 0; i < spriteCount; i++)
        SpriteDraw(sprites[i]);

    EndDrawing();
}

void GameUnload() {
    UnloadTexture(playerTexture);
    UnloadTexture(bgTexture);
}
