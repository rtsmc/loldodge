#include "enemy.h"
#include "sprite.h"
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <time.h>

static void EnemyUpdate(Sprite *self) {
    Enemy *e = (Enemy *)self;
    Vector2 delta = Vector2Subtract(SpritePos(e->target), SpritePos(self));
    e->base.vel = Vector2Scale(delta, e->base.moveSpeed / Vector2Length(delta));
}

static Vector2 genRandomStartPos(float enemyWidth, float enemyHeight) {
    Vector2 out;

    float yMax = GetScreenHeight() + enemyHeight/2;
    float yMin = 0 - enemyHeight/2;
    float xMin = 0 - enemyWidth/2;
    float xMax = GetScreenWidth() + enemyWidth/2;

    srand(time(NULL));
    switch (rand() % 4) {
    case 0:
        out.x = 0 - enemyWidth/2;
        out.y = (rand() % (int)(yMax - yMin + 1)) + 1;
        break;
    case 1:
        out.y = 0 - enemyHeight/2;
        out.x = (rand() % (int)(xMax - xMin + 1)) + 1;
        break;
    case 2:
        out.x = GetScreenWidth() + enemyWidth/2;
        out.y = (rand() % (int)(yMax - yMin + 1)) + 1;
        break;
    case 3:
        out.y = GetScreenHeight() + enemyHeight/2;
        out.x = (rand() % (int)(xMax - xMin + 1)) + 1;
        break;
    }
    return out;
}

void EnemySpawn(Enemy *e) {
    Vector2 startPos = genRandomStartPos(e->base.destRec.width, e->base.destRec.height);
    e->base.destRec.x = startPos.x;
    e->base.destRec.y = startPos.y;
    e->active = true;
}

static const SpriteVtbl enemyVtbl = {
    EnemyUpdate,
};

void EnemyInit(Enemy *e, Texture2D tex, float moveSpeed, Sprite *target) {
    float width = tex.width * 1.8f;
    float height = tex.height * 1.8f;

    e->base.vtbl = &enemyVtbl;
    e->base.tex = tex;
    e->base.destRec = (Rectangle){-10, -10, width, height};
    e->base.moveSpeed = moveSpeed;
    e->base.vel = (Vector2){0, 0};
    e->target = target;
    e->active = false;
}
