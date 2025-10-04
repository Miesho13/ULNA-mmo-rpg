#include "./game.h"
#include "./platform.h"
#include "client.h"
#include "common.h"
#include "server_client_io.h"

#include <string.h>

#define WIDTH 800
#define HEIGHT 800
#define PLAYERS_BUFFER_SIZE (11*11)

static const char *sprite_sheets_path[] = {
    "/home/miesho/programming/c/tibia_like_game_engine/resources/7.0/"
    "Sprites-0.png",
    "/home/miesho/programming/c/tibia_like_game_engine/resources/7.0/"
    "Sprites-1.png",
};

static enum {
    CLIENT_MAIN_SCENE = 0,
    CLIENT_LOGING_SCENE

} SCENE = CLIENT_MAIN_SCENE;

static app_context CORE;

void game_init(void) {
    CORE.game_close = false;
    CORE.window_height = HEIGHT;
    CORE.window_width = WIDTH;
    // CORE.client_context.id = hello_to_server();
    platform_init_window(WIDTH, HEIGHT, "tibia", 144);

    // platform_load_sprite_sheets(sprite_sheets_path, 2);
}

#define TILE_H (HEIGHT / 11)
#define TILE_W (WIDTH  / 11)

//static inline void client_server_move_demo(void) {
//    if (platform_window_shoud_close()) {
//        good_bye(CORE.id);
//        CORE.game_close = true;
//        return;
//    }
//
//    event_loop();
//
//    platform_draw_epilog();
//    platform_clear_background(0x181818FF);
//
//    int x = 0;
//    int y = 0;
//    for (int player = 0; player < 11 * 11; player++) {
//        if (CORE.players[player] != CORE.id && CORE.players[player] != 0) {
//            platform_draw_ractangle(x * TILE_W, y * TILE_H, TILE_W, TILE_H, 0xFF0000FF);
//            char buffer[24] = {0};
//            sprintf(buffer, "%d", CORE.players[player]);
//            platform_draw_text(buffer, x * TILE_W + 30, y * TILE_H, TILE_W, 0xFFFFFFFF);
//
//        } else if (CORE.players[player] == CORE.id) {
//            platform_draw_ractangle(x * TILE_W, y * TILE_H, TILE_W, TILE_H, 0x00FF00FF);
//            char buffer[24] = {0};
//            sprintf(buffer, "%d", CORE.players[player]);
//            platform_draw_text(buffer, x * TILE_W + 30, y * TILE_H, TILE_W, 0xFFFFFFFF);
//
//        }
//
//        x++;
//        if (x % 11 == 0 && x != 0) {
//            y++;
//            x = 0;
//        }
//    }
//    platform_draw_prolog();
//}

int game_run(void) {
    game_init();

    while (!CORE.game_close) {
        switch(SCENE) {
            case CLIENT_MAIN_SCENE: { 
                main_scene_step(&CORE); 
                break; 
            }

            case CLIENT_LOGING_SCENE: {
                break;
            }
        }
    }

    return 0;
}


