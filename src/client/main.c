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
    resource_load_vram(&text_ctx, "./resources/Sprites-%d.png", 30, 2);
    sprites_list_t *list = rend_sprites_list_init(32);
    
    int x = 0; 
    int y = 0; 
    for (int i = 0; i < 10; i++) {
        rend_sprites_list_add(
            list, (sprite_t){
                &text_ctx.text[0], 
                (Vector2){x*32*2, y*32*2}
            }
        );

        if (x++ == 4) { x = 0; y++; }
    }
    
    rend_sprites_list_add(list, (sprite_t) {&text_ctx.text[1], (Vector2){1*32*2, 0*32*2}});
    while (WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(WHITE);
        DrawFPS(screenWidth-124, 0);
        rend_list(list);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
