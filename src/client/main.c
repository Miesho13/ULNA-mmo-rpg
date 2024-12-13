#include <assert.h>
#include <bits/posix1_lim.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

#include "raylib.h"
#include "renderer.h"
#include "sprite_data.h"

const int screenWidth = 800;
const int screenHeight = 600;

bool has_time_elapsed(float *lastTime, float interval) {
    float currentTime = GetTime();
    if ((currentTime - *lastTime) >= interval) {
        *lastTime = currentTime;
        return true;
    }
    return false;
}

int main(void) {
    InitWindow(screenWidth, screenHeight, "tibia game");
    SetTargetFPS(144);

    renderer_ctx_t rctx;
    renderer_init(&rctx, &game_sprite_load_ctx, 1.5);

    int animatein_start = (12*12)*3 - 11;
    int animation_count = animatein_start;
    float last_time = 0.0f;
    float interval = 0.2f;

    int animation_frame[] = {
        animatein_start,
        animatein_start + 1,
        animatein_start,
        animatein_start + 1,
        animatein_start,
        animatein_start + 1,
        animatein_start + 2,
        animatein_start + 3,
    };

    uint32_t i = 0;
    while (WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(SKYBLUE);

        int32_t x = 0;
        int32_t y = 0;

        // for (uint32_t i = 0; i < 12*12; i++) {
        //     DrawTexture(rctx.text_buffer[i], x*32, y*32, WHITE);
        //     x++;
        //     if (x == 12 ) { x = 0; y++; }
        // }

        DrawTexture(rctx.text_buffer[animation_frame[i % 8]], 400, 300, WHITE);

        if (has_time_elapsed(&last_time, interval)) {
            i++;
        }

        DrawFPS(screenWidth-124, 0);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
