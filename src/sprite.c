#include "sprite.h"
#include <raylib.h>
#include <raymath.h>

void SpriteMove(Sprite *s) {
    if (s->vtbl->move) {
        s->vtbl->move(s);
        return;
    }

    s->destRec.x += s->vel.x * GetFrameTime();
    s->destRec.y += s->vel.y * GetFrameTime();
}

void SpriteUpdate(Sprite *s) {
    if (s->vtbl->update)
        s->vtbl->update(s);
}

void SpriteDraw(Sprite *s) {
    if (s->vtbl->draw) {
        s->vtbl->draw(s);
        return;
    }

    int frameWidth = s->tex.width;
    int frameHeight = s->tex.height;
    int sourceWidth = frameWidth;
    sourceWidth = s->vel.x >= 0 ? sourceWidth : -1 * sourceWidth;

    DrawTexturePro(
        s->tex,
        (Rectangle){0.0f, 0.0f, (float)sourceWidth, (float)frameHeight},
        s->destRec, (Vector2){(float)frameWidth, (float)frameHeight}, 0.0f,
        RAYWHITE);

}

Vector2 SpritePos(Sprite *s) { return (Vector2){s->destRec.x, s->destRec.y}; }
