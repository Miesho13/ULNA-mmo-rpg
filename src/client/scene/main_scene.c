#include "../game.h"
#include "../platform.h"
#include "../client.h"
#include "main_scene_cfg.h"
#include "common.h"
#include "server_client_io.h"

#include <string.h>

typedef struct {
    bool is_init;
    app_context *app;

    struct {
        int x;
        int y;
    } pos;

    struct {
        int dx;
        int dy;
    } dpos;

    event_t event;
    event_t event_to_handle[EVENT_MAX_SIZE];
    uint16_t player_tile_map[MAIN_SCENE_TILE_BUFF_SIZE];

} main_scene_context;

static main_scene_context CORE;

static inline void log_in_to_server(void) {
    CORE.app->client_context.id = hello_to_server();
    if (CORE.app->client_context.id < 0) {
        CORE.app->client_context.login = false; 
        LOG(LOG_ERROR, "We cannot log in to the game server.");
    }
    CORE.app->client_context.login = true; 
}

static inline void server_communication(void) {
    if (CORE.app->client_context.login == false) {
        return;
    }

    event_request_t event_request = {0};

    event_request.head    = UPDATE;
    event_request.dpos.dx = CORE.dpos.dx;
    event_request.dpos.dy = CORE.dpos.dy;
    event_request.event   = CORE.event;

    client_push_event(&event_request);

    // handle server respone 
    update_respone_t update_respone = {0};
    client_recv_update_event(&update_respone);
    
    memcpy(CORE.event_to_handle, update_respone.events, EVENT_MAX_SIZE);
    memcpy(CORE.player_tile_map, update_respone.player_map, MAIN_SCENE_TILE_BUFF_SIZE);
}

/* Hanel an users's inputs */ 
static inline void set_dpos(int dx, int dy) {
    CORE.dpos.dx = dx; 
    CORE.dpos.dx = dy; 
}

/*
 * Checks the current state of the keyboard for movement keys
 * (W/A/S/D or arrow keys). Depending on which key is pressed,
 * it updates the player’s delta position by calling `set_dpos()`
 * with the appropriate direction vector:
 *   - Left  (A or ←)  → (-1,  0)
 *   - Right (D or →)  → ( 1,  0)
 *   - Up    (W or ↑)  → ( 0,  1)
 *   - Down  (S or ↓)  → ( 0, -1) 
 */
static inline void position_change_event(void) {
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
        set_dpos(0, 1);
    }
    else if (platform_key_down(PLATFORM_KEY_S) ||  
            platform_key_down(PLATFORM_KEY_DOWN)) {
        set_dpos(0, -1);
    }
}

static inline void input_event(void) {
    position_change_event();
}


static inline void init_if_need(app_context *app) {
    if (CORE.is_init) {
        return;
    }

    if (app) {
        CORE.app = app;
    }

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
    
    // handle game server
    server_communication();
    
    // render scene
     
}
