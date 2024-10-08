#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "raylib.h"
#include "resource.h"
#include "renderer.h"

const int screenWidth = 800;
const int screenHeight = 600;

int main(void) {
    InitWindow(screenWidth, screenHeight, "tibia game");
    SetTargetFPS(144);

    sprites_list_t *list = rend_sprites_list_init(32);
    printf("head: %p\nsize: %d\nsize_max: %d\n\n", 
            (void*)list->head, 
            list->size, 
            list->size_max);
    
       
    for (int i = 0; i < 32; i++) {
        printf("%d: head->next: %p head->val %p %f %f\n", 
                i, (void*)list->head->next,
                (void*)list->head->val.texutre,
                list->head->val.pos.x,
                list->head->val.pos.y);

        list->head = list->head->next;
    }

    sprite_node *node = prv_iterate_element(list, 12);
    node->val.pos.x = 5;
    node->val.pos.y = 5;


    for (int i = 0; i < 32; i++) {
        printf("%d: head->next: %p head->val %p %f %f\n", 
                i, (void*)list->head->next,
                (void*)list->head->val.texutre,
                list->head->val.pos.x,
                list->head->val.pos.y);

        list->head = list->head->next;
    }

    while (WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(WHITE);

        DrawFPS(screenWidth-124, 0);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
