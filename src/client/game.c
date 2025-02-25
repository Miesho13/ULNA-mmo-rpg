#include "game.h"
#include "renderer.h"
#include "game_config.h"
#include "dynamic_array.h"



static void draw_backgraund(game_context_t *game_ctx) {
    vec_render_obj backgraund
        = vec_array_new(TILE_GAME_SIZE, sizeof(render_obj));

    int sizie_file = 0;
    uint8_t *buffer = LoadFileData("./map/output", &sizie_file);

    int x_pos = 0; int y_pos = 0;
    uint32_t scale = game_ctx->game_renderer.scale_sprite_width;
    for (int i = 0; i < TILE_GAME_SIZE; i++) {
        vec_push(
            backgraund,
            &(render_obj) {
            (Vector2){x_pos*scale, y_pos*scale},
            buffer[i]
        });
        x_pos++;
        if (x_pos == 15) { y_pos++; x_pos = 0; }
    }
    free(buffer);

    rend_draw_vector(&game_ctx->game_renderer, backgraund);
}

static void move_logic(game_context_t *game_ctx) {

}

static void draw_obj(game_context_t *game_ctx) {

}

void game_frame(game_context_t *game_ctx) {
    // Logic of the clinet
    move_logic(game_ctx);

    // Draw the result for user
    BeginDrawing();

    ClearBackground(BLACK);

    draw_backgraund(game_ctx);
    draw_obj(game_ctx);

    EndDrawing();
}
