#ifndef SPRITE_H
#define SPRITE_H

#include <raylib.h>

typedef struct Sprite Sprite;
typedef struct SpriteVtbl SpriteVtbl;

struct SpriteVtbl {
  void (*update)(struct Sprite *);
  void (*draw)(struct Sprite *);
  void (*move)(struct Sprite *);
};

struct Sprite {
  const SpriteVtbl *vtbl;
  Texture2D tex;
  Rectangle destRec;
  float moveSpeed;
  Vector2 vel;
};

void SpriteUpdate(Sprite *self);
void SpriteDraw(Sprite *self);
void SpriteMove(Sprite *self);

#endif
