#include "../game.h"
#include "../platform.h"
#include "../client_config.h"

#include "scene.h"

#include <unistd.h>
#include <string.h>

typedef struct {
    app_context *app;
    bool is_init;
    
    struct {
        v2_i32 start_pos;
        v2_i32 end_pos;
    } picker_pos[SCENE_COUNT]; 

} login_screan_state;

static login_screan_state CORE;

inline static void input_event(void) {
    if (platform_mouse_button_pressed(PLATFORM_MOUSE_BUTTON_LEFT)) {
     
    }
}

inline static void draw_scene_picker(void) {
    platform_draw_prolog();

    v2_i32 center_pos = {CORE.app->window_width/2, CORE.app->window_height/2};
    
    v2_i32 pos_with_pading = {
        .x = center_pos.x - ((float)CORE.app->window_width/2)*(1.f - LOGIN_SCREAN_PADDING_W),
        .y = 0 + CORE.app->window_height*LOGIN_SCREAN_PADDING_H
    };

    // draw scene picker 
    for (size_t idx = 1; idx < SCENE_COUNT; idx++) {
        scene_t scene = scene_get_avaliable_scene_id(idx);

        // update picker text posytion 
        CORE.picker_pos[idx].start_pos = (v2_i32){ .x = pos_with_pading.x, .y = pos_with_pading.y };
        int x_end = pos_with_pading.x + LOGIN_SCREAN_FONT_SIZE*strlen(scene.name);
        int y_end = pos_with_pading.y + LOGIN_SCREAN_FONT_SIZE;
        CORE.picker_pos[idx].end_pos = (v2_i32){ .x = x_end, .y = y_end };
        
        int x_mause = platform_get_mause_x();
        int y_mause = platform_get_mause_y();

        uint32_t font_color = LOGIN_SCREAN_FONT_COLOR;
        if(x_mause >= CORE.picker_pos[idx].start_pos.x
                && x_mause <= CORE.picker_pos[idx].end_pos.x 
                && y_mause >= CORE.picker_pos[idx].start_pos.y 
                && y_mause <= CORE.picker_pos[idx].end_pos.y) {
            font_color = platform_color_brightness(font_color, 0.5);

            if (platform_mouse_button_pressed(PLATFORM_MOUSE_BUTTON_LEFT)) {
                scene_set(idx);
            }
        }

        platform_draw_text(
            scene.name, 
            pos_with_pading.x, 
            pos_with_pading.y, 
            LOGIN_SCREAN_FONT_SIZE, 
            font_color
        );


        // new text possition
        pos_with_pading.y += LOGIN_SCREAN_FONT_SIZE + LOGIN_SCREAN_MARGIN_TEXT;

    }
    
    platform_draw_epilog();
}

int scene_pick() {
    v2_i32 pos = {0};
    if (platform_mouse_button_pressed(PLATFORM_MOUSE_BUTTON_LEFT)) {
        v2_i32 pos = platform_get_mause();
    }
}

void init(app_context* app) {
    if (CORE.is_init) {
        return;
    }

    if (!app) {
        return;
    }

    CORE.app = app;
    CORE.is_init = true;
}

void scene_login_screan(app_context *app) {
    if (platform_window_shoud_close()) {
        app->game_close = true;
        return;
    }
    init(app);
    draw_scene_picker();
    scene_pick();
}
