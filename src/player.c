#include "player.h"
#include <raylib.h>

static void PlayerUpdate(Sprite *self) {}

static void PlayerDraw(Sprite *self) {
    int frameWidth = self->tex.width;
    int frameHeight = self->tex.height;

    DrawTexturePro(
        self->tex,
        (Rectangle){0.0f, 0.0f, (float)frameWidth, (float)frameHeight},
        self->destRec, (Vector2){(float)frameWidth, (float)frameHeight}, 0.0f,
        RAYWHITE);
}

void PlayerInit(Player *p, Texture2D tex, Vector2 startPos, float moveSpeed) {
    p->base.update = PlayerUpdate;
    p->base.draw = PlayerDraw;
    p->base.tex = tex;
    p->base.destRec = (Rectangle){startPos.x, startPos.y, tex.width * 1.8f,
                                  tex.height * 1.8f};
    p->base.moveSpeed = moveSpeed;
    p->base.vel = (Vector2){0, 0};
    p->dest = (Vector2){startPos.x, startPos.y};
    p->hasDest = false;
}
