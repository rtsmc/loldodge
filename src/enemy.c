#include "sprite.h"
#include "enemy.h"
#include <raylib.h>

static void EnemyUpdate(Sprite *self) {

}

static const SpriteVtbl enemyVtbl = {
    EnemyUpdate,
};

static Vector2 genRandomStartPos() {
}

void EnemyInit(Enemy* e, Texture2D tex, float moveSpeed) {
    e->base.vtbl = &enemyVtbl;
    e->base.tex = tex;
    Vector2 startPos = genRandomStartPos();
    e->base.destRec = (Rectangle){startPos.x, startPos.y, tex.width * 1.8f,
                                  tex.height * 1.8f};
    e->base.moveSpeed = moveSpeed;
    e->base.vel = (Vector2){0, 0};
}
