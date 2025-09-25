#include "./game.h"
#include "./platform.h"
#include "client.h"

#define WIDTH 800
#define HEIGHT 600

static const char *sprite_sheets_path[] = {
    "/home/miesho/programming/c/tibia_like_game_engine/resources/7.0/Sprites-0.png",
    "/home/miesho/programming/c/tibia_like_game_engine/resources/7.0/Sprites-1.png",
};

typedef struct _game_context {
    int window_width;
    int window_height;
} game_context;

static game_context game_ctx;

void game_init(void) {
    game_ctx.window_height = HEIGHT;
    game_ctx.window_height = WIDTH;

    platform_load_sprite_sheets(sprite_sheets_path, 2);
}

void render_frame(uint8_t* plain);

void game_run(void) {
    client_init();
    uint8_t msg[] = "CLIENT HELLO\r\n";
    client_send(msg, sizeof(msg));

    platform_init_window(WIDTH, HEIGHT, "tibia", 144);

    while (!platform_window_shoud_close()) {
        platform_draw_epilog();

        platform_clear_background(0x181818FF);
        platform_draw_ractangle(100, 100, 200, 200, 0xFF0000FF);

        platform_draw_prolog();
    }
}

