#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "raylib.h"
#include "renderer.h"
#include "sprite_data.h"

const int screenWidth = 800;
const int screenHeight = 600;

int main(void) {
    InitWindow(screenWidth, screenHeight, "tibia game");
    SetTargetFPS(144);

    renderer_ctx_t rctx;
    renderer_init(&rctx, &game_sprite_load_ctx, 1);

    while (WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(SKYBLUE);

        int32_t x = 0;
        int32_t y = 0;

        for (uint32_t i = 0; i < 12*12; i++) {
            DrawTexture(rctx.text_buffer[i], x*32, y*32, WHITE);
            x++;
            if (x == 12 ) { x = 0; y++; }
        }

        DrawFPS(screenWidth-124, 0);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
