#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <stdint.h>
#include <stdlib.h>

#include "raylib.h"
#include "sprite_data.h"
#include "sprite_data.h"

typedef struct {
    uint32_t h;
    uint32_t w;
} image_size_px;

typedef struct {
    Texture2D *texutre;
    Vector2 pos;
} sprite_t;

typedef struct sprite_node sprite_node;
struct sprite_node {
    sprite_node *next;
    sprite_t val;
};

typedef struct {
    sprite_node *head;
    uint32_t size;
    uint32_t size_max;
    uint32_t counter_end;
} render_vector;

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


void renderer_init(renderer_ctx_t *rctx, sprite_loader_path_t *sprite_data, double scale);

void renderer_load_text(renderer_ctx_t *rctx);
void renderer_free_text(renderer_ctx_t *rctx);

render_vector*  render_vecotr_init(uint32_t max_size);
void            render_vecotr_push(render_vector *vec, sprite_t val);
sprite_t        render_vecotr_get(render_vector *vec, uint32_t index);
sprite_t        render_vecotr_pop(render_vector *vec, uint32_t index);
void            render_buffer(renderer_ctx_t *rctx, render_vector *list);
#endif
