#include "../game.h"
#include "../platform/platform.h"
#include "../client.h"
#include "main_scene_cfg.h"
#include "common.h"
#include "server_client_io.h"
#include "../common/time_bench.h"

#include <string.h>
#include <unistd.h>

typedef struct {
    bool is_init;
    app_context *app;

    struct {
        int x;
        int y;
    } pos;

    struct {
        uint32_t h;
        uint32_t w;
    } tail_size;

    struct {
        int dx;
        int dy;
    } dpos;

    event_t event;
    event_t event_to_handle[EVENT_MAX_SIZE];
    map_grid player_tile_map[MAIN_SCENE_TILE_BUFF_SIZE];

    struct {
        bool debug_dump_info;
        double server_comm_delay;
    } bench;

} main_scene_context;

static main_scene_context CORE;

static inline void log_in_to_server(void) {
    CORE.app->client_context.id = hello_to_server();
    if (CORE.app->client_context.id < 0) {
        CORE.app->client_context.login = false; 
        LOG(COMMON_LOG_ERROR, "We cannot log in to the game server.");
    }
    CORE.app->client_context.login = true; 
}

static inline void clear_after_send() {
    // HERE SHOUD BE RESET ALL SATE WHAT WE NEED TO SEND ONCE 
    CORE.dpos.dx = 0;
    CORE.dpos.dy = 0;

    memset(&CORE.event, 0, sizeof(CORE.event));
}

static inline void server_communication(void) {
    if (CORE.app->client_context.login == false) {
        return;
    }

    time_start();
    
    update_request_t update_request = {0};

    update_request.head    = UPDATE;
    update_request.id      = CORE.app->client_context.id;
    update_request.dpos.dx = CORE.dpos.dx;
    update_request.dpos.dy = CORE.dpos.dy;
    update_request.event   = CORE.event;

    client_push_event(&update_request);

    // TODO: Need to make some lifetime and timestamp for comunication
    //       if some recv dont come we shoud make recive 
  
    // handle server respone 
    update_respone_t update_respone = {0};
    client_recv_update_event(&update_respone);
    
    memcpy(CORE.event_to_handle, update_respone.events, sizeof(event_t)*EVENT_MAX_SIZE);
    memcpy(CORE.player_tile_map, update_respone.player_map, 
           sizeof(map_grid) * MAIN_SCENE_TILE_BUFF_SIZE);

    clear_after_send();

    CORE.bench.server_comm_delay = time_end_ns() / 1000000.f;

    printf("INCOMING DATA:\n");
        printf("\tupdate_respone.events:\n");
    for (int i = 0; i < 12; i++) {
        printf("\tevent: [%d %d (%d %d)]\n", 
                update_respone.events[i].action, 
                update_respone.events[i].player_id, 
                update_respone.events[i].relative_pos.x,
                update_respone.events[i].relative_pos.y);
    }
    printf("update_respone.head %d\n", update_respone.head);
    printf("update_respone.pos.x %d\n", update_respone.pos.x);
    printf("update_respone.pos.y %d\n", update_respone.pos.y);
}

/* Hanel an users's inputs */ 
static inline void set_dpos(int dx, int dy) {
    CORE.dpos.dx = dx; 
    CORE.dpos.dy = dy; 
}

/*
 * Checks the current state of the keyboard for movement keys
 * (W/A/S/D or arrow keys). Depending on which key is pressed,
 * it updates the player’s delta position by calling `set_dpos()`
 * with the appropriate direction vector:
 *   - Left  (A or ←)  → (-1,  0)
 *   - Right (D or →)  → ( 1,  0)
 *   - Up    (W or ↑)  → ( 0, -1)
 *   - Down  (S or ↓)  → ( 0,  1) 
 */
static inline void position_change_event(void) {
    // TODO: Need some sample rate how many offen we read the imput form user 
    
    if (platform_key_down(PLATFORM_KEY_A) ||  
            platform_key_down(PLATFORM_KEY_LEFT)) {
        set_dpos(-1, 0);
    }
    else if (platform_key_down(PLATFORM_KEY_D) ||  
            platform_key_down(PLATFORM_KEY_RIGHT)) {
        set_dpos(1, 0);
    }
    else if (platform_key_down(PLATFORM_KEY_W) ||  
            platform_key_down(PLATFORM_KEY_UP)) {
        set_dpos(0, -1);
    }
    else if (platform_key_down(PLATFORM_KEY_S) ||  
            platform_key_down(PLATFORM_KEY_DOWN)) {
        set_dpos(0, 1);
    }
}

static inline void eval_mause_click(const v2_i32 pos) {
    int click_pos_x = pos.x/CORE.tail_size.w;
    int click_pos_y = pos.y/CORE.tail_size.h;

    CORE.event.action = EV_CLICK;
    CORE.event.relative_pos.x  = click_pos_x;
    CORE.event.relative_pos.y  = click_pos_y;

    LOG(COMMON_LOG_INFO, "(%d %d)", click_pos_x, click_pos_y);
}

static inline void mose_input_event(void) {
    if (platform_mouse_button_pressed(PLATFORM_MOUSE_BUTTON_LEFT)) {
        v2_i32 pos = platform_get_mause();
        eval_mause_click(pos);
    }
}

static inline void input_event(void) {
    position_change_event();
    mose_input_event();

    if (platform_key_press(PLATFORM_KEY_N)) {
        CORE.bench.debug_dump_info ^= 1;
    }
}

static inline void drump_deb_info(bool dumb) {
    if (dumb == false) {
        return;
    }

    v2_i32 pos = platform_get_mause();

    char ms[3*64] = {0};
    sprintf(ms, "ms: %5.2f\n"
                "player_id: %d\n"
                "mause_pos: (%d, %d)\n",
            CORE.bench.server_comm_delay,
            CORE.app->client_context.id,
            pos.x/CORE.tail_size.w, pos.y/CORE.tail_size.h);

    platform_draw_text(ms, 0, 0, 20, 0x2bf21dff);
}

static inline void render_players_demo(void) {
    int tile_h = CORE.app->window_height / 11;
    int tile_w = CORE.app->window_width  / 11;

    int x = 0;
    int y = 0;
    for (int player = 0; player < 11 * 11; player++) {
        if (CORE.player_tile_map[player].posytion != CORE.app->client_context.id && CORE.player_tile_map[player].posytion != 0) {
            platform_draw_ractangle(x * tile_w, y * tile_h, tile_w, tile_h, 0xFF0000FF);
            char buffer[24] = {0};
            sprintf(buffer, "%d", CORE.player_tile_map[player].posytion);
            platform_draw_text(buffer, x * tile_w + 30, y * tile_h, tile_w, 0xFFFFFFFF);

        } else if (CORE.player_tile_map[player].posytion == CORE.app->client_context.id) {
            platform_draw_ractangle(x * tile_w, y * tile_h, tile_w, tile_h, 0x00FF00FF);
            char buffer[24] = {0};
            sprintf(buffer, "%d", CORE.player_tile_map[player].posytion);
            platform_draw_text(buffer, x * tile_w + 30, y * tile_h, tile_w, 0xFFFFFFFF);

        }

        x++;
        if (x % 11 == 0 && x != 0) {
            y++;
            x = 0;
        }
    }
}

static inline void render_plain(void) {
    platform_draw_prolog();
    platform_clear_background(0x153699ff);

    // DRAW DEBUG INFO
    render_players_demo();
    drump_deb_info(CORE.bench.debug_dump_info);

    platform_draw_epilog();
}

static inline void init_if_need(app_context *app) {
    if (CORE.is_init) {
        return;
    }

    if (app) {
        CORE.app = app;
    }

    CORE.tail_size.h = CORE.app->window_height / 11;
    CORE.tail_size.w = CORE.app->window_width  / 11;

    // TODO(marcin.ryzewski): move this to login scene 
    log_in_to_server();
    
    CORE.is_init = true;
} 

void main_scene_step(app_context *app) {
    if (platform_window_shoud_close()) {
        app->game_close = true;
        return;
    }

    // Ensures that initialization code for the main scene runs only once.
    // If the scene has already been initialized (`CORE.is_init == true`),
    // the function exits early. Otherwise, this is where all necessary
    // setup logic should be placed before marking the scene as initialized.
    init_if_need(app);

    // handle all input events from the user 
    input_event();
    
    server_communication();

    render_plain();

    // render scene
}
