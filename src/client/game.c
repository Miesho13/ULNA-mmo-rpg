#include "./game.h"
#include "./platform.h"
#include "client.h"
#include "common.h"
#include "server_client_io.h"
#include "scene/scene.h"

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

inline static void window_update(void) {
    CORE.window_height = platform_get_win_height();
    CORE.window_width = platform_get_win_width();
}

int game_run(void) {
    game_init();

    while (!CORE.game_close) {
        window_update();
        scene_show(&CORE);
    }

    return 0;
}


