#ifndef ENEMY_H
#define ENEMY_H

#include "sprite.h"

#include <raylib.h>

typedef struct Enemy {
  Sprite base;
  Sprite *target;
  bool active;
} Enemy;

void EnemySpawn(Enemy *e);
void EnemyInit(Enemy *e, Texture2D tex, float moveSpeed, Sprite *target);

#endif
