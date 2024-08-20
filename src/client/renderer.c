#include "renderer.h"

void renderer_update(sprite_vec_t *sprites) {
    BeginDrawing();
    for (uint32_t draw_id = 0; draw_id < sprites->size; draw_id++) {
        DrawTexture(
            *sprites->sprites[draw_id].sprite, 
            sprites->sprites[draw_id].pos.x, 
            sprites->sprites[draw_id].pos.y, WHITE);
    }
    EndDrawing();
}
