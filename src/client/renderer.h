#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <stdint.h>
#include "raylib.h"


typedef struct {
    Texture2D *sprite;
    Vector2 pos;
} sprite_t;

typedef struct {
   sprite_t *sprites;  
   uint32_t size;
} sprite_vec_t;

void renderer_update(sprite_vec_t *vtail);

#endif
