#include "tile.h"

void tile_set(tile_plane *ctx, platform_sprite sprite, 
              v2_i32 pos, platform_sprite *out) {
    assert(out && "buffers can be NULL");
    out[(pos.y*ctx->layer_h) + pos.x] = sprite; 
}

void tile_render_sprite(tile_plane *ctx, platform_sprite *sprite, int pos_x, int pos_y) {
    platform_render(sprite, pos_x*ctx->sprite_size.w, pos_y*ctx->sprite_size.h, 0xffffffff);
}

void tile_render_plane(tile_plane *ctx, platform_sprite *sprite) {
    assert(ctx && sprite && "param cant be NULL");

    const size_t tiles_max = ctx->layer_w*ctx->layer_h;

    int x = 0, y = 0;
    for (size_t sprite_id = 0; sprite_id < tiles_max; sprite_id++) {
        platform_render(
            &sprite[sprite_id], 
            x*ctx->sprite_size.w, 
            y*ctx->sprite_size.h, 
            0xffffffff
        );

        x++;
        if (x >= ctx->layer_h) {
            x = 0;
            y++;
        }
    }
}

void tile_render_layer(tile_plane *tile, uint32_t *sprites) {
    assert(tile && "tile cant be null");

    const size_t layer_max = tile->layer_w * tile->layer_h;

    int x = 0, y = 0;
    for (size_t sprite_id = 0; sprite_id < layer_max; sprite_id++) {
        platform_render(
            &tile->sprites->sprite[sprites[sprite_id]], 
            x * tile->sprite_size.w, 
            y*tile->sprite_size.h, 
            0xffffffff
        );

        x++;
        if (x >= tile->layer_h) {
            x = 0;
            y++;
        }
    }
}
