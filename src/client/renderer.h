#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <stdint.h>
#include <stdlib.h>
#include "raylib.h"


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

} sprites_list_t;

sprites_list_t* rend_sprites_list_init(uint32_t max_size);

void rend_sprites_list_add(sprites_list_t *llist, sprite_t val);

sprite_t rend_sprites_list_get(sprites_list_t *llist, uint32_t index);

void rend_list(sprites_list_t *list);
#endif

