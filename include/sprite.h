#ifndef SPRITE_H
#define SPRITE_H

#include <raylib.h>

struct Sprite;

typedef struct Sprite {
  void (*update)(struct Sprite *);
  void (*draw)(struct Sprite *);
  Texture2D tex;
  Rectangle destRec;
  float moveSpeed;
  Vector2 vel;
} Sprite;

void SpriteMove(Sprite* self);
void SpriteUpdate(Sprite* self);
void SpriteDraw(Sprite* self);

#endif
