#include "../game.h"
#include "../platform/platform.h"
#include "../client.h"
#include "main_scene_cfg.h"
#include "common.h"
#include "server_client_io.h"
#include "../common/time_bench.h"
#include "../renderer.h"
#include "../tile.h"
#include "../client_config.h"
#include "../ui.h"

#include <string.h>
#include <unistd.h>


typedef struct {
    bool is_init;
    app_context *app;

    struct {
        struct {
            int x;
            int y;
        } game_pos;

    } player_context; 

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


    tile_plane tile_ctx;
    ui_context ui_context;

    struct {
        render_sprite_vector sprite_context;
        platform_sprite background[TILES_PER_PLANE];
    } render_buffers;

    struct {
        uint32_t background[TILES_PER_PLANE];
        uint32_t npc[TILES_PER_PLANE];
    } layers;

    event_t event;
    event_t event_to_handle[EVENT_MAX_SIZE];
    map_grid player_tile_map[MAIN_SCENE_TILE_BUFF_SIZE];

    struct {
        bool debug_dump_info;
        double server_comm_delay;
        double plain_load_us;
    } bench;

} main_scene_context;

static main_scene_context CORE;

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
    
    if (platform_key_press(PLATFORM_KEY_A) ||  
            platform_key_press(PLATFORM_KEY_LEFT)) {
        CORE.player_context.game_pos.x -= 1;
    }
    else if (platform_key_press(PLATFORM_KEY_D) ||  
            platform_key_press(PLATFORM_KEY_RIGHT)) {
        CORE.player_context.game_pos.x += 1;

    }
    else if (platform_key_press(PLATFORM_KEY_W) ||  
            platform_key_press(PLATFORM_KEY_UP)) {
        CORE.player_context.game_pos.y -= 1;
    }
    else if (platform_key_press(PLATFORM_KEY_S) ||  
            platform_key_press(PLATFORM_KEY_DOWN)) {
        CORE.player_context.game_pos.y += 1;
    }
}

static inline void eval_mause_click(const v2_i32 pos) {
    int click_pos_x = pos.x/CORE.tail_size.w;
    int click_pos_y = pos.y/CORE.tail_size.h;

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
    // mose_input_event();

    if (platform_key_press(PLATFORM_KEY_P)) {
        ui_remove(&CORE.ui_context, 1);
    }

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

    sprintf(ms,// "ms: %5.2f\n"
               // "player_id: %d\n"
               // "mause_pos: (%d, %d)\n"
               "parse plain: (%f us)\n",
               // CORE.bench.server_comm_delay,
               // CORE.app->client_context.id,
               // pos.x/CORE.tail_size.w, pos.y/CORE.tail_size.h,
               CORE.bench.plain_load_us/1000000);

    platform_draw_text(ms, 0, 0, 20, 0x2bf21dff);
}

static void render_background(void) 
{
    for (int id = 0; id < TILES_PER_PLANE; ++id) {
        CORE.layers.background[id] = (3*RENDER_PLAIN_W+5);
    }

    tile_render_layer(&CORE.tile_ctx, CORE.layers.background);
}

static void render_ui(void) 
{
    // platform_render(&CORE.ui_context.asset_gpu[0], 0, 0, 0xFFFFFFFF);
    ui_render(&CORE.ui_context);
}

static inline void render_frame(void) 
{
    // platform_draw_prolog();
    // platform_clear_background(0x4d4f8cff);
    // render_background();

    // drump_deb_info(CORE.bench.debug_dump_info);
    // platform_draw_epilog();
    
     platform_draw_prolog();
     platform_clear_background(0x4d4f8cff);

     platform_draw_line(10, 10, 100, 100, 2.0, 0xFF0000FF);

     platform_relative_mode_prolog(100, 300); {
         platform_draw_line(10, 10, 100, 100, 2.0, 0xFFFF00FF);
         platform_draw_line(100, 100, 150, 50, 2.0, 0xFFFF00FF);
     } platform_relative_mode_epilog();

     platform_draw_line(100, 100, 150, 50, 2.0, 0xFF0000FF);

     platform_draw_epilog();
}

static void load_plains(void) 
{
    const char tmp[255] = {0};

    for (int i = 0; i < 30; i++) {
        sprintf((char*)tmp, "./../resources/7.1/Sprites-%d.png", i);

        render_load_sprite_from_plain(
            &CORE.render_buffers.sprite_context, tmp,
            (v2_i32){.x = 32, .y = 32}, 2.0
        );
    }

    ui_load_assets(&CORE.ui_context, "./../ui-assets/ui-plane.png");
}

// Initializes core application settings and context. Prepares the necessary resources,
// configures initial states, and sets up user interface elements for the application.
static inline void init(app_context *app) 
{
    if (CORE.is_init) {
        return;
    }

    if (app) {
        CORE.app = app;
    }

    time_start();
    load_plains();
    CORE.bench.plain_load_us = (float)time_end_ns() / 1000000;

    CORE.tile_ctx.layer_h = TILES_H;
    CORE.tile_ctx.layer_w = TILES_W;
    CORE.tile_ctx.sprite_size.h = CORE.render_buffers.sprite_context.sprite[0].height;
    CORE.tile_ctx.sprite_size.w = CORE.render_buffers.sprite_context.sprite[0].width;
    CORE.tile_ctx.sprites = &CORE.render_buffers.sprite_context;

    CORE.player_context.game_pos.x = 20;
    CORE.player_context.game_pos.y = 20;

    CORE.is_init = true;
} 

void render_test_scene(app_context *app) 
{
    if (platform_window_shoud_close()) {
        app->game_close = true;
        return;
    }

    // Ensures that initialization code for the main scene runs only once.
    // If the scene has already been initialized (`CORE.is_init == true`),
    // the function exits early. Otherwise, this is where all necessary
    // setup logic should be placed before marking the scene as initialized.
    init(app);

    // handle all input events from the user 
    // input_event();
    render_frame();

}
