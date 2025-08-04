#ifndef ENEMY_H
#define ENEMY_H

#include "sprite.h"

#include <raylib.h>

typedef struct Enemy {
    Sprite base;
} Enemy;

void EnemyInit(Enemy* e, Texture2D tex, float moveSpeed);

#endif
