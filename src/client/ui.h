#ifndef _UI_H_
#define _UI_H_

#include "client_config.h"
#include "platform.h"

#include <stdbool.h>

typedef struct {
    int pos_x;
    int pos_y;
    int h;
    int w;
} assets_meta_data;

typedef struct {
    platform_img    asset_img[UI_ASSETS_SIZE_BUFFER];
    platform_sprite asset_gpu[UI_ASSETS_SIZE_BUFFER];
    size_t asset_count;

    struct {
        void *ui_head;
        int element_count;
    } render;

} ui_context;

typedef enum {
    UI_MSG_BOX = 0,
    UI_BUTTON,

    UI_NONE = 0xff,
} ui_element_type;

typedef enum {
    UI_VISABLE = 1 << 0,
    UI_MOVABLE = 1 << 1,
} ui_flags;

typedef struct {
    int id;
    int prio;
    ui_element_type type;
    uint32_t flags;

    struct {
        int x;
        int y;
    } pos;

    struct {
        int height;
        int width;
    } size;

    platform_sprite sprite;
    double scale;

    void *next;
} ui_element;

typedef struct {
    ui_element ui_element;
    const char *text;
} ui_msg_box;


void ui_load_assets(ui_context *ctx, const char *path);
void ui_event_loop(ui_context *ctx);
void ui_render(ui_context *ctx);
void ui_remove(ui_context *ui, int id);

void ui_element_change_pos(ui_context *ui_ctx, int new_x, int new_y);
void ui_element_press(ui_context *ui_ctx, v2_i32 cursor_pos);

int ui_push_msg_box(ui_context *ui_ctx, const char *msg, int pos_x, int pos_y, double scale);

#endif // _UI_H_
