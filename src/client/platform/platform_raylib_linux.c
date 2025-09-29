#include "../platform.h"
#include "raylib.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

static struct {
    Image sprite_sheets[SPRITE_SHEETS_MAX_COUNT];
    Image image_vector[SPRITE_SHEETS_MAX_COUNT];
} platform_context;

void platform_draw_prolog(void) {
    BeginDrawing();
}

void platform_draw_epilog(void) {
    EndDrawing();
}

void platform_clear_background(uint32_t color) {
    Color cl = {
        .r = (color & 0xFF000000) >> 8*3,
        .g = (color & 0x00FF0000) >> 8*2,
        .b = (color & 0x0000FF00) >> 8*1,
        .a = (color & 0x000000FF) >> 8*0
    };
    ClearBackground(cl);
}

void platform_init_window(int width, int height, const char *title, int target_fps) {
    InitWindow(width, height, title);
    SetTargetFPS(target_fps);
}

bool platform_window_shoud_close(void) {
    return WindowShouldClose();
}

void platform_load_sprite_sheets(const char **sprite_sheets_path, size_t image_count) {
    for (size_t i = 0; i < image_count; i++) {
        platform_context.sprite_sheets[i] = LoadImage(sprite_sheets_path[i]);
    }
}

void platform_draw_ractangle(int posX, int posY, int width, int height, uint32_t color) {
    Color cl = {
        .r = (color & 0xFF000000) >> 8*3,
        .g = (color & 0x00FF0000) >> 8*2,
        .b = (color & 0x0000FF00) >> 8*1,
        .a = (color & 0x000000FF) >> 8*0
    };

    DrawRectangle(posX, posY, width, height, cl);
}

bool platform_key_press(keyboard_key key) {
    return IsKeyPressed(key);
}

void platform_draw_text(const char *text, int posX, int posY, int fontSize, uint32_t color) {
    Color cl = {
        .r = (color & 0xFF000000) >> 8*3,
        .g = (color & 0x00FF0000) >> 8*2,
        .b = (color & 0x0000FF00) >> 8*1,
        .a = (color & 0x000000FF) >> 8*0
    };
    DrawText(text, posX, posY, fontSize, cl);
}


