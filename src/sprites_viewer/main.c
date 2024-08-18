#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "../client/resource.h"
#include "raylib.h"

const int screenWidth = 800;
const int screenHeight = 600;

void print_res_with_id(resource_texture_t *ctx, Camera2D *cam) {
    uint32_t x = 0;
    uint32_t y = 0;

    BeginDrawing();
    ClearBackground(WHITE);

    BeginMode2D(*cam);

    for (uint32_t i = 0; i < ctx->size; i++) {
        DrawTexture(ctx->text[i], x*32*ctx->scale, y*32*ctx->scale, WHITE);

        if ((x % 32 == 0) && (x != 0)) {
            y++;
            x = -1;
        }
        x++;
    }

    x = 0;
    y = 0;
    char tmp[RES_SPRITE_PER_IMG];
    for (uint32_t i = 0; i < ctx->size; i++) {
        sprintf(tmp, "0x%x", i);
        DrawText(tmp, x * 32*ctx->scale, y * 32*ctx->scale, 6*ctx->scale, RED);
        if (x % 32 == 0 && x != 0) {
            y++;
            x = -1;
        }
        x++;
    }

    EndMode2D();
    EndDrawing();
}

int main(void) {
    InitWindow(screenWidth, screenHeight, "Sprite Viewer");
    SetTargetFPS(60);
    
    resource_texture_t text_ctx = {0};
    resource_load_vram(&text_ctx, "./resources/Sprites-%d.png", 30, 2);

    Camera2D camera = {
        .offset = (Vector2){0.0f, 0.0f},
        .target = (Vector2){0.0f, 0.0f},
        .rotation = 0.0f,
        .zoom = 1.0f,
    };

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_RIGHT)) camera.target.x += 8;
        if (IsKeyDown(KEY_LEFT)) camera.target.x -= 8;
        if (IsKeyDown(KEY_UP)) camera.target.y -= 8;
        if (IsKeyDown(KEY_DOWN)) camera.target.y += 8;

        if (IsKeyDown(KEY_Z)) camera.zoom += 0.01f;
        if (IsKeyDown(KEY_X)) camera.zoom -= 0.01f;

        print_res_with_id(&text_ctx, &camera);
    }
    CloseWindow();
    return 0;
}
