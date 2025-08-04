#include "player.h"
#include "sprite.h"
#include <raylib.h>
#include <raymath.h>

static bool MouseOnPlayer(Sprite *self) {
    return GetMouseX() > self->destRec.x - self->destRec.width / 2 &&
           GetMouseX() < self->destRec.x + self->destRec.width / 2 &&
           GetMouseY() > self->destRec.y - self->destRec.height / 2 &&
           GetMouseY() < self->destRec.y + self->destRec.height / 2;
}

static void PlayerUpdate(Sprite *self) {
    Player *p = (Player *)self;

    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON) && !MouseOnPlayer(self)) {
        float w = self->destRec.width;
        float h = self->destRec.height;

        p->dest =
            (Vector2){Clamp(GetMouseX(), 0 + w / 2, GetScreenWidth() - w / 2),
                      Clamp(GetMouseY(), 0 + h / 2, GetScreenHeight() - h / 2)};
        p->hasDest = true;

        Vector2 delta = (Vector2){p->dest.x - p->base.destRec.x,
                                  p->dest.y - p->base.destRec.y};
        p->base.vel =
            Vector2Scale(delta, p->base.moveSpeed / Vector2Length(delta));
    }

    if (p->hasDest) {
        Vector2 dist = (Vector2){p->dest.x - p->base.destRec.x,
                                 p->dest.y - p->base.destRec.y};
        if (Vector2LengthSqr(dist) < 0.5f) {
            p->base.vel = Vector2Zero();
            p->base.destRec.x = p->dest.x;
            p->base.destRec.y = p->dest.y;
            p->hasDest = false;
        }
    }
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

static const SpriteVtbl playerVtbl = {
    PlayerUpdate,
    PlayerDraw
};

void PlayerInit(Player *p, Texture2D tex, Vector2 startPos, float moveSpeed) {
    p->base.vtbl = &playerVtbl;
    p->base.tex = tex;
    p->base.destRec = (Rectangle){startPos.x, startPos.y, tex.width * 1.8f,
                                  tex.height * 1.8f};
    p->base.moveSpeed = moveSpeed;
    p->base.vel = (Vector2){0, 0};
    p->dest = (Vector2){startPos.x, startPos.y};
    p->hasDest = false;
}
