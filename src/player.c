#include "player.h"
#include "sprite.h"
#include <raylib.h>
#include <raymath.h>

static void PlayerUpdate(Sprite *self) {
    Player *p = (Player *)self;

    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
        p->dest = (Vector2){GetMouseX(), GetMouseY()};
        p->hasDest = true;

        Vector2 delta = (Vector2){p->dest.x - p->base.destRec.x,
            p->dest.y - p->base.destRec.y};
        p->base.vel = Vector2Scale(delta, p->base.moveSpeed/Vector2Length(delta));
    }

    if (p->hasDest) {
        Vector2 dist = (Vector2){p->dest.x - p->base.destRec.x, p->dest.y - p->base.destRec.y};
        if (Vector2LengthSqr(dist) < 10) {
            p->base.vel = Vector2Zero();
            p->base.destRec.x = p->dest.x;
            p->base.destRec.y = p->dest.y;
            p->hasDest = false;
        }
    }
    SpriteMove(self);
}

static void PlayerDraw(Sprite *self) {
    int frameWidth = self->tex.width;
    int frameHeight = self->tex.height;
    int sourceWidth = frameWidth;
    sourceWidth = self->vel.x >= 0 ? sourceWidth : -1 * sourceWidth;

    DrawTexturePro(
        self->tex,
        (Rectangle){0.0f, 0.0f, (float)sourceWidth, (float)frameHeight},
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
