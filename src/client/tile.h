#ifndef __TILE__
#define __TILE__

#include <stdint.h>
#include "renderer.h"
#include "resource.h"

typedef struct { 
    uint32_t draw;
    uint32_t sprite_id;
    Vector2 pos;
} tile_t;



typedef struct { 
    tile_t buffer[64]; 
    resource_texture_t *hres;
    uint32_t weight;
    uint32_t height;
    uint32_t size;

} tile_field_t;

void tile_init(tile_field_t *ctx, resource_texture_t *res, uint32_t weight,
    uint32_t height);

// int tile_get_srpite_vec(tile_field_t *ctx, sprite_vec_t *vec);

void tile_add(tile_field_t *ctx, uint32_t sprite_id, uint32_t posX,
    uint32_t posY);

void tile_clear(tile_field_t *ctx, uint32_t posX, uint32_t posY);

#endif

