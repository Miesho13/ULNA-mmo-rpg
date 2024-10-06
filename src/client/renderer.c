#include "renderer.h"
#include <stdlib.h>


static inline void* prv_create_node(void) {
    return calloc(1, sizeof(sprite_node));
}

static void* prv_resize_list() {

}

sprite_node* prv_iterate_element(sprites_list_t *llist, uint32_t index) {
    sprite_node *current = llist->head->next;
    for (uint32_t iter = 0; iter < index; iter++) {
        current = current->next; 
    }
    return current;
}

static void prv_create_nodes(sprites_list_t *llist) {
    llist->head = prv_create_node();
    sprite_node *tmp = prv_create_node();
    llist->head->next = tmp;

    for (uint32_t current_node_index = 0; 
            current_node_index < llist->size_max - 2; current_node_index++) {
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
    
    

    llist->size++;


}

// void renderer_update(sprite_vec_t *sprites) {
//     BeginDrawing();
//     for (uint32_t draw_id = 0; draw_id < sprites->size; draw_id++) {
//         DrawTexture(
//             *sprites->sprites[draw_id].sprite, 
//             sprites->sprites[draw_id].pos.x, 
//             sprites->sprites[draw_id].pos.y, WHITE);
//     }
//     EndDrawing();
// }
