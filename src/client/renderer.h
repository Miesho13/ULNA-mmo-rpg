#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "common.h"
#include "client_config.h"
#include "platform.h"

#include <stdint.h>
#include <stdlib.h>

typedef enum {
    RENDER_ERR_OK  = 0,
    RENDER_ERR_ERR,
} render_err;

typedef struct {
    uint8_t *data;
    int height;
    int width;
} tails;

typedef struct {
    platform_img img[RENDER_MAX_SPRITE_SIZE];
    platform_sprite sprite[RENDER_MAX_SPRITE_SIZE];
    size_t sprite_count;
    float scale;
} render_sprite_vector;

render_err render_load_sprite_from_plain(render_sprite_vector *ctx, const char *path, 
                                         v2_i32 sprite_size, float scale);


// void render_plain(tails *draw_bufffer, size_t len, const int HEIGHT, const int WIDTH);


#endif
