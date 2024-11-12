#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <stdint.h>
#include <stdlib.h>
#include "raylib.h"
#include "resource.h"

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
    resource_texture_t resource_ctx;
} renderer_ctx;


void renderer_init(resource_texture_t *renderer_ctx);
render_vector*  render_vecotr_init(uint32_t max_size);
void            render_vecotr_push(render_vector *vec, sprite_t val);
sprite_t        render_vecotr_get(render_vector *vec, uint32_t index);
sprite_t        render_vecotr_pop(render_vector *vec, uint32_t index);
void            render_buffer(sprites_list_t *list);
#endif

