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

void draw_ui() {}

void draw_game() {
    resource_context_t *res_ctx = resource_get_context();

    BeginDrawing();
    uint32_t row = 0;
    uint32_t colum = 0;
    for (uint8_t draw_id = 0; draw_id < 255; draw_id++) {
        DrawTexture(res_ctx->sprite[draw_id], 32 * colum++, row, WHITE);
        if (draw_id % 10 == 0 && draw_id != 0) {
            colum = 0;
            row += 32;
        }
    }
    EndDrawing();
}

void draw_frame() {
//    draw_ui();
//    draw_game();
}

int main(void) {
    init_game();
    resource_init();

    Camera2D camera = { 
        .offset = 0,
        .target = (Vector2){ 0.0f, 0.0f },
        .rotation = 0.0f,
        .zoom = 1.0f,
    };
    

    while (!WindowShouldClose()) {

        if (IsKeyDown(KEY_RIGHT)) camera.target.x += 4;
        if (IsKeyDown(KEY_LEFT)) camera.target.x -= 4;
        if (IsKeyDown(KEY_UP)) camera.target.y -= 4;
        if (IsKeyDown(KEY_DOWN)) camera.target.y += 4;

        if (IsKeyDown(KEY_Z)) camera.zoom += 0.01f;
        if (IsKeyDown(KEY_X)) camera.zoom -= 0.01f;

        print_res_with_id(&camera);
    }
    CloseWindow();
    return 0;
}
