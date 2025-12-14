#include "./platform.h"
#include "raylib.h"
#include "common.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

static struct {
    Image sprite_sheets[SPRITE_SHEETS_MAX_COUNT];
    Image image_vector[SPRITE_SHEETS_MAX_COUNT];
} platform_context;

uint32_t platform_color_brightness(uint32_t color, float scale) {
    int r = (color & 0xFF000000) >> 24;
    int g = (color & 0x00FF0000) >> 16;
    int b = (color & 0x0000FF00) >> 8;
    int a = (color & 0x000000FF);

    r *= scale;
    g *= scale;
    b *= scale;

    return (uint32_t)(r << 24 | g << 16 | b << 8 | a);
}

int platform_get_win_height(void) {
    return GetScreenHeight();
}

int platform_get_win_width(void) {
    return GetScreenWidth();
}

void platform_draw_prolog(void) {
    BeginDrawing();
}

void platform_draw_epilog(void) {
    EndDrawing();
}

void platform_draw_line(int start_x, int start_y, int end_x, int end_y, float thick, uint32_t color)
{
    Color cl = {
        .r = (color & 0xFF000000) >> 8*3,
        .g = (color & 0x00FF0000) >> 8*2,
        .b = (color & 0x0000FF00) >> 8*1,
        .a = (color & 0x000000FF) >> 8*0
    };

    DrawLineEx((Vector2){start_x, start_y}, (Vector2){end_x, end_y}, thick, cl);
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
    SetTraceLogLevel(LOG_NONE);

    InitWindow(width, height, title);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(target_fps);
}

bool platform_window_shoud_close(void) {
    return WindowShouldClose();
}

platform_img platform_load_img(const char *path) {
    Image img = LoadImage(path);
    platform_img ret = {0};
    memcpy(&ret, &img, sizeof(ret));

    return ret;
}

platform_img platform_load_img_from_image(platform_img img, int x, int y, int width, int height) {
    Image img_ray;
    memcpy(&img_ray, &img, sizeof(img_ray));

    img_ray = ImageFromImage(img_ray, (Rectangle){x, y, width, height});
    memcpy(&img, &img_ray, sizeof(img));

    return img; 
}


platform_sprite platform_load_to_gpu(void *img) {
    Image *_img = (void*)img;
    Texture2D texture = LoadTextureFromImage(*_img);
    platform_sprite dst;
    memcpy(&dst, &texture, sizeof(dst));
    return dst;
}

void platform_scissor_mode(int x, int y, int width, int height)
{
    BeginScissorMode(x, y, width, height);
}

void platform_end_scissor_mode(void)
{
    EndScissorMode();
}

void platform_img_resize(void *img, int w, int h) {
    ImageResize(img, w, h);
}

void platform_render(void *sprite, int x, int y, uint32_t color) {
    Color cl = {
        .r = (color & 0xFF000000) >> 8*3,
        .g = (color & 0x00FF0000) >> 8*2,
        .b = (color & 0x0000FF00) >> 8*1,
        .a = (color & 0x000000FF) >> 8*0
    };

    DrawTexture(*(Texture2D*)sprite, x, y, cl);
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

bool platform_key_down(keyboard_key key) {
    return IsKeyDown(key);
}

bool platform_key_relased(keyboard_key key) {
    return IsKeyReleased(key);
}

bool platform_key_up(keyboard_key key) {
    return IsKeyUp(key);
}

bool platform_key_pressed_pepeat(keyboard_key key) {
    return IsKeyPressedRepeat(key);
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

bool platform_mouse_button_pressed(int button) {
    return IsMouseButtonPressed(button);
}

bool platform_mouse_button_down(int button) {
    return IsMouseButtonDown(button);
}

bool platform_mouse_button_released(int button) {
    return IsMouseButtonReleased(button);
}

bool platform_mouse_button_up(int button) {
    return IsMouseButtonUp(button);
}

int platform_get_mause_x(void) {
    return GetMouseX();
}

int platform_get_mause_y(void) {
    return GetMouseY();
}

v2_i32 platform_get_mause(void) {
    return (v2_i32){platform_get_mause_x(), platform_get_mause_y()};
}

int platform_mesure_text(const char *text, int fontSize) {
    return MeasureText(text, fontSize);
}

platform_img platform_img_copy(void *img) {
    Image copy_img = ImageCopy(*(Image*)img);
    platform_img ret_img = {0};
    memcpy(&ret_img, &copy_img, sizeof(Image));
    return ret_img;
}

void platform_unload_sprite(void *sprite) {
    UnloadTexture(*(Texture2D*)sprite);
}
