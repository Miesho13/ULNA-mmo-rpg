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
    
    renderer_ctx rctx;
    renderer_init(&rctx, "resources/Sprites-%d.png", 30, 1);

    while (WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(WHITE);
        DrawFPS(screenWidth-124, 0);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
