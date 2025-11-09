#ifndef _TILE_H_
#define _TILE_H_

#include "renderer.h" 

typedef struct {
    int tile_h;
    int tile_w;

    struct {
        int w;
        int h;
    } sprite_size; 

} tile_plane; 

void tile_init(tile_plane *ctx, int sprite_w, int sprite_h, int tile_h, int tile_w);
void tile_set(tile_plane *ctx, platform_sprite sprite, 
              v2_i32 pos, platform_sprite *out);
void tile_render_sprite(tile_plane *ctx, platform_sprite *sprite, int pos_x, int pos_y);
void tile_render_plane(tile_plane *ctx, platform_sprite *sprite);
     

#endif
