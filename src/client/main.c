#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

#include "raylib.h"
#include "resource.h"

const int screenWidth = 1980;
const int screenHeight = 1080;

void init_game(void) {
    InitWindow(screenWidth, screenHeight, "tibia game");
    SetTargetFPS(60);
}



void test_canvas(uint32_t *data, uint32_t size, uint32_t w, uint32_t h, 
        uint32_t offx, uint32_t offy) {
    
    res_ctx_h resh = resource_get_context();

    BeginDrawing();
    ClearBackground(WHITE);
     
    for (uint32_t draw_id = 0; draw_id < size; draw_id++) {
        DrawText(resh->text_sprite[draw_id], draw);
    }

    EndDrawing();
}

void print_res_with_id(Camera2D *cam) {
    resource_context_t *ctx = resource_get_context();
    uint32_t x = 0;
    uint32_t y = 0;

    BeginDrawing();
    ClearBackground(WHITE);
    
    

    // draw bacgraund
    for (uint32_t i = 0; i < ctx->sprite_count; i++) {
         
    }

    BeginMode2D(*cam);

    for (uint32_t i = 0; i < ctx->sprite_count; i++) {
        DrawTexture(ctx->text_sprite[i], x*32*ctx->scale, y*32*ctx->scale, WHITE);
        if ((x % 64 == 0) && (x != 0)) {
            y++;
            x = -1;
        }
        x++;
    }

    EndMode2D();
    EndDrawing();
}

int main(void) {
    init_game();
    reso_load_image("./resources/Sprites-%d.png", RES_MAX_IMG_TO_LOAD, 2);
    res_ctx_h hres = resource_get_context();

    Camera2D camera = { 
        .offset = 0,
        .target = (Vector2){ 0.0f, 0.0f },
        .rotation = 0.0f,
        .zoom = 1.0f,
    };

    uint32_t animation_start = 0xfa2;
    uint32_t animation_end = 0xfb8;
    uint32_t animation = animation_start;
    while (!WindowShouldClose()) {

        ClearBackground(BLACK);

        BeginDrawing();

        DrawTexture(hres->text_sprite[animation++], screenWidth/2, screenHeight/2, WHITE);

        EndDrawing();

        if (animation == animation_end) {
            animation = animation_start;
        }
        WaitTime(1);
    }

    CloseWindow();
    return 0;
}
