#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdbool.h>

#include "raylib.h"
#include "resource.h"
#include "renderer.h"
#include "tile.h"

const int screenWidth = 1980;
const int screenHeight = 1080;

int main(void) {
    InitWindow(screenWidth, screenHeight, "tibia game");
    SetTargetFPS(60);

    resource_texture_t text_ctx; 
    resource_load_vram(&text_ctx, "./resources/Sprites-%d.png", 1, 2);
    
    tile_field_t tile_field = {0};
    tile_init(&tile_field, &text_ctx, 8, 8);

    for (int y = 0; y < 6; y++) {
    for (int x = 0; x < 6; x++) {
        tile_add(&tile_field, 0x0, x, y);
    }}

    tile_add(&tile_field, 0x7, 3, 3);

    sprite_t sprite_buff[64] = {0};
    sprite_vec_t sprite_vec = {
        .size = 0,
        .sprites = sprite_buff
    }; 
    tile_get_srpite_vec(&tile_field, &sprite_vec);

    while (WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(WHITE);

        renderer_update(&sprite_vec);

        DrawFPS(screenWidth-124, 0);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
