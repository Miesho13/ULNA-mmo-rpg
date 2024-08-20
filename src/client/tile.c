#include <string.h>
#include "tile.h"
#include "resource.h"

static uint32_t prv_take_pos(tile_field_t *ctx, uint32_t pos_x, uint32_t pos_y) {
    return (uint32_t)((pos_y * ctx->weight) + pos_x);
}

static Vector2 prv_tile_to_sprite_pos(Vector2 vec, uint32_t scale) {
    return (Vector2) {.x = vec.x*32*scale, .y = vec.y*32*scale};
}

void tile_init(tile_field_t *ctx, resource_texture_t *res, uint32_t weight, uint32_t height) {
    ctx->height = height;
    ctx->weight = weight;
    ctx->size = 64;
    ctx->hres = res;
}

int tile_get_srpite_vec(tile_field_t *ctx, sprite_vec_t *vec) {
    uint32_t sprite_id = 0;
    vec->size = 0;
    for (uint32_t tile_id = 0; tile_id < ctx->size; tile_id++) {
        if (ctx->buffer[tile_id].draw == 0) {
            continue; 
        } else {
            vec->sprites[sprite_id].pos = prv_tile_to_sprite_pos(
                ctx->buffer[tile_id].pos, 
                ctx->hres->scale);
            vec->sprites[sprite_id].sprite 
                = &(ctx->hres->text[ctx->buffer[tile_id].sprite_id]);
            vec->size++;
            sprite_id++;
        }
    }
    return vec->size;
}

void tile_add(tile_field_t *ctx, uint32_t sprite_id, uint32_t posX, uint32_t posY) {
    ctx->buffer[prv_take_pos(ctx, posX, posY)].sprite_id = sprite_id;
    ctx->buffer[prv_take_pos(ctx, posX, posY)].pos.x = posX;
    ctx->buffer[prv_take_pos(ctx, posX, posY)].pos.y = posY;
    ctx->buffer[prv_take_pos(ctx, posX, posY)].draw = 1;
}

void tile_clear(tile_field_t *ctx, uint32_t posX, uint32_t posY) {
    memset(
        &ctx->buffer[prv_take_pos(ctx, posX, posY)], 
        0, sizeof(tile_t));
}
