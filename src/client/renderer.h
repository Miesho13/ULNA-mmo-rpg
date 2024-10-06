#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <stdint.h>
#include <stdlib.h>
#include "raylib.h"


//typedef struct {
//    Texture2D *sprite;
//    Vector2 pos;
//} sprite_t;
//
//typedef struct {
//   sprite_t *sprites;  
//   uint32_t size;
//} sprite_vec_t;
//
//
//
//typedef struct {
//    sprite_t *head;
//    sprite_t *next;
//    size_t size; 
//} sprite_stack_t;
//
//
//void renderer_update(sprite_vec_t *vtail);

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
} sprites_list_t;

sprites_list_t* rend_sprites_list_init(uint32_t max_size);
sprite_node* prv_iterate_element(sprites_list_t *llist, uint32_t index);

#endif
