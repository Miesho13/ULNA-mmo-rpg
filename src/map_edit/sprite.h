#ifndef __SPRIE_H__
#define __SPRIE_H__

#include "../platform/platform.h"
#include "../client/client_config.h"
#include "common.h"

typedef enum {
    RENDER_OK  = 0,
    RENDER_ERR,
} render_err;

typedef struct {
    platform_img img[RENDER_MAX_SPRITE_SIZE];
    platform_sprite sprite[RENDER_MAX_SPRITE_SIZE];
    size_t sprite_count;
    float scale;
} sprite_context;

render_err render_load_sprite_from_plain(sprite_context *ctx, const char *path, 
                                         v2_i32 sprite_size, float scale);

void load_sprite(sprite_context *ctx_sprite);
void render_sprite(sprite_context *ctx, int id, int x, int y);

#endif // __SPRIE_H__
