#include "./game.h"
#include "./platform.h"
#include "client.h"
#include "common.h"
#include "server_client_io.h"

#include <string.h>

#define WIDTH 800
#define HEIGHT 800

static const char *sprite_sheets_path[] = {
    "/home/miesho/programming/c/tibia_like_game_engine/resources/7.0/Sprites-0.png",
    "/home/miesho/programming/c/tibia_like_game_engine/resources/7.0/Sprites-1.png",
};

typedef struct _game_context {
    int window_width;
    int window_height;

    uint32_t id;
    struct {
        int x;
        int y;
    } pos;
    uint8_t players[11*11];

} game_context;

static game_context game_ctx;

void game_init(void) {
    game_ctx.window_height = HEIGHT;
    game_ctx.window_height = WIDTH;

    platform_load_sprite_sheets(sprite_sheets_path, 2);
}

void render_frame(uint8_t* plain);

int hello_to_server() {
    client_init();
    uint8_t msg[] = { 0x11 };
    client_send(msg, sizeof(msg));

    uint8_t request[124];
    client_recv(request, sizeof(request));

    return ((register_respone_t*)request)->id;
}

void chang_pos(int id, int dx, int dy) {
    event_request_t request = {
        .head = MOVE,
        .id = id,
        .dpos = {
            .dx = dx,
            .dy = dy 
        }
    };
    client_send((uint8_t*)&request, sizeof(request));

    uint8_t respone[124] = {0};
    client_recv(respone, sizeof(respone));

    memcpy(game_ctx.players, ((event_respone_t*)respone)->players, sizeof(game_ctx.players));

    LOG(INFO, "new pos: x:%d y:%d", 
            ((event_respone_t*)respone)->pos.x,
            ((event_respone_t*)respone)->pos.y);

}

void good_bye() {
    good_bye_request_t request = {
        .head = GOOD_BYE,
        .id = game_ctx.id,
    };
    client_send((uint8_t*)&request, sizeof(request));
}

static void event_loop(void) {
    if (platform_key_press(PLATFORM_KEY_A) || platform_key_press(PLATFORM_KEY_LEFT)) {
        chang_pos(game_ctx.id, -1, 0);
    }
    else if (platform_key_press(PLATFORM_KEY_D) || platform_key_press(PLATFORM_KEY_RIGHT)) {
        chang_pos(game_ctx.id, 1, 0);
    }
    else if (platform_key_press(PLATFORM_KEY_S) || platform_key_press(PLATFORM_KEY_DOWN)) {
        chang_pos(game_ctx.id, 0, 1);
    }
    else if (platform_key_press(PLATFORM_KEY_W) || platform_key_press(PLATFORM_KEY_UP)) {
        chang_pos(game_ctx.id, 0, -1);
    } 
    else {
        chang_pos(game_ctx.id, 0, 0);
    }
}

#define TILE_H (HEIGHT / 11)
#define TILE_W (WIDTH  / 11)

void game_run(void) {
    game_ctx.id = hello_to_server();

    platform_init_window(WIDTH, HEIGHT, "tibia", 144);
    
    while (true) {
        if (platform_window_shoud_close()) {
            good_bye();
            break;
        }

        event_loop();

        platform_draw_epilog();
        platform_clear_background(0x181818FF);

        // DRAW MAIN PLAYER 
        // platform_draw_ractangle(WIDTH/2 - 16, HEIGHT/2 - 16, 32, 32, 0xFF0000FF);

        // DRAW OTHER PLAER
        //
        

        int x = 0; int y = 0;
        for (int player = 0; player < 11*11; player++) {
            if (game_ctx.players[player] == 1) {
                platform_draw_ractangle(x*TILE_W, y*TILE_H, TILE_W, TILE_H, 0xFF0000FF);
            }
            else if (game_ctx.players[player] == 2) {
                platform_draw_ractangle(x*TILE_W, y*TILE_H, TILE_W, TILE_H, 0x00FF00FF);
            }

            x++;
            if (x % 11 == 0 && x != 0) {
                y++;
                x = 0;
            }
        }
        platform_draw_prolog();
    }
}

