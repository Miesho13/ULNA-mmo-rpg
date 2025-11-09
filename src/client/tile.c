#include "tile.h"

void tile_set(tile_plane *ctx, platform_sprite sprite, 
              v2_i32 pos, platform_sprite *out) {
    assert(out && "buffers can be NULL");
    out[(pos.y*ctx->tile_w) + pos.x] = sprite; 
}

void tile_render_sprite(tile_plane *ctx, platform_sprite *sprite, int pos_x, int pos_y) {
    platform_render(sprite, pos_x*ctx->sprite_size.w, pos_y*ctx->sprite_size.h, 0xffffffff);
}

void tile_render_plane(tile_plane *ctx, platform_sprite *sprite) {
    assert(ctx && sprite && "param cant be NULL");

    const size_t tiles_max = ctx->tile_w*ctx->tile_h;

    int x = 0, y = 0;
    for (size_t sprite_id = 0; sprite_id < tiles_max; sprite_id++) {
        platform_render(&sprite[sprite_id], x*ctx->sprite_size.w, y*ctx->sprite_size.h, 0xffffffff);

        x++;
        if (x >= ctx->tile_w) {
            x = 0;
            y++;
        }
    }
}
