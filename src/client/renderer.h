#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <stdint.h>
#include <stdlib.h>

#include "dynamic_array.h"
#include "raylib.h"
#include "sprite_data.h"
#include "sprite_data.h"

typedef vec_array vec_render_obj;

typedef struct {
    Vector2 pos;
    uint32_t id;
} render_obj;

typedef struct {
    Image *image_buffer;
    size_t image_buffer_size;

    Texture *text_buffer;
    size_t text_buffer_size;

    char *path_to_sprites_sheet;
    double scale;

    // TODO(marcin.ryzewskii@gmail.com): Can we have a problem
    // with precision in dobule can we?
    double sprite_width;
    double sprite_height;

} renderer_ctx_t;

void rend_init(renderer_ctx_t *rctx, sprite_loader_path_t *sheet_data, double scale);
void rend_draw_vector(const renderer_ctx_t *rctx, const vec_array objects_v);

#endif
