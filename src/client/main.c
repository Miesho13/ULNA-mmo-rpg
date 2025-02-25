#include <assert.h>
#include <bits/posix1_lim.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

#include "raylib.h"
#include "renderer.h"
#include "sprite_data.h"
#include "game.h"

const int screenWidth = 1920;
const int screenHeight = 1080;

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
    
    game_context_t game_ctx;
    rend_init(&game_ctx.game_renderer, &game_sprite_load_ctx, 2);

    while (WindowShouldClose() == false) {
        game_frame(&game_ctx);
    }

    CloseWindow();
    return 0;
}
