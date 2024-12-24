#include <assert.h>
#include <bits/posix1_lim.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>

#include "raylib.h"
#include "renderer.h"
#include "sprite_data.h"
#include "dynamic_array.h"


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
    rend_init(&rctx, &game_sprite_load_ctx, 1.7);

    int animatein_start = (12*12)*3 - 11;
    float last_time = 0.0f;
    float interval = 0.2f;
    
    vec_array texts_vec = vec_array_new(20, sizeof(render_obj));
    Vector2 posytion = {0};
    for (uint32_t i = 0; i < vec_capasity(texts_vec); i++) {
        vec_push(texts_vec, &((render_obj){(Vector2){posytion.x*rctx.sprite_width, posytion.y*rctx.sprite_height}, 0}));
        posytion.x += 1.f;
        if (posytion.x == 6.f) {
            posytion.y += 1.f; 
            posytion.x = 0;
        }
    }

    uint32_t i = 0;
    while (WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(SKYBLUE);

        if (has_time_elapsed(&last_time, interval)) {
            i++;
        }
    
        rend_draw_vector(&rctx, texts_vec);

        DrawFPS(screenWidth-124, 0);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
