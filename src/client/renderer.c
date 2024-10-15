#include "renderer.h"
#include <stdlib.h>
#include <string.h>


static inline void* prv_create_node(void) {
    return calloc(1, sizeof(sprite_node));
}

static void* prv_resize_list() { }

static sprite_node* prv_iterate_element(sprites_list_t *llist, uint32_t index) {
    sprite_node *current = llist->head;
    
    uint32_t iter = 0;
    while (current->next != NULL) {
        if (iter++ == index ) {
            break;
        }
        current = current->next; 
    }

    return current;
}

static void prv_create_nodes(sprites_list_t *llist) {
    llist->head = prv_create_node();
    sprite_node *tmp = prv_create_node();
    llist->head->next = tmp;

    for (uint32_t current_node_index = 0; 
         current_node_index < llist->size_max - 2; 
         current_node_index++
    ){
        tmp->next = prv_create_node();
        tmp = tmp->next;
    }
}

sprites_list_t* rend_sprites_list_init(uint32_t max_size) {
    sprites_list_t *ret = calloc(1, sizeof(*ret));
    ret->size_max = max_size;
    prv_create_nodes(ret);

    return ret;
}

void rend_sprites_list_add(sprites_list_t *llist, sprite_t val) {
    if (llist->size >= llist->size_max) {
        return;
    }
    
    sprite_node *node = prv_iterate_element(llist, llist->size);
    memcpy(&node->val, &val, sizeof(val));
    llist->size++;
}

sprite_t rend_sprites_list_get(sprites_list_t *llist, uint32_t index) {
    sprite_node* node = prv_iterate_element(llist, index);
    sprite_t ret;
    memcpy(&ret, &node->val, sizeof(ret));

    return ret;
}

void rend_list(sprites_list_t *list) {
    BeginDrawing();
    for (uint32_t i = 0; i < list->size; i++) {
        sprite_t tmp = rend_sprites_list_get(list, i);
        DrawTexture(
            *tmp.texutre,
            tmp.pos.x, tmp.pos.y,
            WHITE
        );
    }
    EndDrawing();
}
