#ifndef PLAYER_H
#define PLAYER_H

#include "sprite.h"

#include <raylib.h>

typedef struct Player {
  Sprite base;
  Vector2 dest;
  bool hasDest;
} Player;

void PlayerInit(Player* p, Texture2D tex, Vector2 startPos, float moveSpeed);

#endif
