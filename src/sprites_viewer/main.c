#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "raylib.h"
#include "renderer.h"
#include "sprite_data.h"

const int screenWidth = 800;
const int screenHeight = 600;

typedef enum {
    INPUT_MOV,
    INPUT_CHAR,
} INPUT_MODE_t;

INPUT_MODE_t mode;

renderer_ctx_t rctx;

Camera2D camera = {
    .offset = (Vector2){0.0f, 0.0f},
    .target = (Vector2){0.0f, 0.0f},
    .rotation = 0.0f,
    .zoom = 1.0f,
};

struct _search_buffer {
    uint8_t buffer[1024];
    uint32_t len;
} search_buffer = {0};
int form = 0;
int to = 0;

void input(void) {
    if (mode == INPUT_MOV) {
        if (IsKeyDown(KEY_SLASH)) mode = INPUT_CHAR;
        if (IsKeyDown(KEY_RIGHT)) camera.target.x += 8;
        if (IsKeyDown(KEY_LEFT)) camera.target.x -= 8;
        if (IsKeyDown(KEY_UP)) camera.target.y -= 8;
        if (IsKeyDown(KEY_DOWN)) camera.target.y += 8;
        if (IsKeyDown(KEY_Z)) camera.zoom += 0.01f;
        if (IsKeyDown(KEY_X)) camera.zoom -= 0.01f;
    }
    else {
        search_buffer.buffer[search_buffer.len] = (uint8_t)GetCharPressed();

        if (IsKeyDown(KEY_ESCAPE)) mode = INPUT_MOV;
        if (IsKeyDown(KEY_ESCAPE)) {

        }
    }
}

void crate_draw_buffer() {
    float x = 0, y = 0;
    for (uint32_t text_id = 0; text_id < rctx.text_buffer_size; text_id++) {
        DrawTexture(
            rctx.text_buffer[text_id],
            rctx.sprite_width*x++,
            rctx.sprite_height*y,
            WHITE);

        if (rctx.sprite_height*x >= screenWidth) {x = 0; y++;}
    }
}

int main(void) {
    InitWindow(screenWidth, screenHeight, "Sprite Viewer");
    SetTargetFPS(60);
    SetExitKey(0);

    renderer_init(&rctx, &game_sprite_load_ctx, 1.5);

    while (!WindowShouldClose()) {
        input();

        BeginDrawing();
        ClearBackground(SKYBLUE);

        BeginMode2D(camera);                          // Begin 2D mode with custom camera (2D)

        crate_draw_buffer();
        EndMode2D();                                       // Ends 2D mode with custom camera

        DrawRectangle(0, screenHeight - 20, screenWidth, 20, BLUE);
        (mode == INPUT_MOV) ?
            DrawText("MOVE", 0, screenHeight - 20, 16, RED) :
            DrawText("INPUT_CHAR", 0, screenHeight - 20, 16, RED);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
