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
    resource_texture_t text_ctx = {0};
    resource_load_vram(&text_ctx, "./resources/Sprites-%d.png", 30, 1);
    sprites_list_t *list = rend_sprites_list_init(32);

    printf("head: %p\nsize: %d\nsize_max: %d\n\n", 
            (void*)list->head, 
            list->size, 
            list->size_max);
    
    for (int i = 0; i < 32; i++) {
        rend_sprites_list_add(
            list, (sprite_t){&text_ctx.text[i+30], (Vector2){i*32, 0}}
        );
    }

    while (WindowShouldClose() == false) {
        ClearBackground(WHITE);
        DrawFPS(screenWidth-124, 0);

        rend_list(list);
    }

    CloseWindow();
    return 0;
}
