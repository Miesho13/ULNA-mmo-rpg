#include <stdio.h>

#include "client_conf.h"
#include "resource.h"

static resource_context_t ctx = {};

void resource_init() {
    char path_buff[MAX_STRING_BUFF] = {0};
    Image loaded_image[IMAGE_MAX_COUNT];
    for (uint8_t imgindex = 0; imgindex < IMAGE_MAX_COUNT; imgindex++) {
        sprintf(path_buff, "./resources/Sprites-%d.png", imgindex);
        loaded_image[imgindex] = LoadImage(path_buff);
    }

    uint32_t sprite_index = 0;
    for (uint16_t sprites = 0; sprites < 30; sprites++) {
        for (uint16_t y_cord = 0; y_cord < 12; y_cord++) {
            for (uint16_t x_cord = 0; x_cord < 12; x_cord++) {
                ctx.sprite[sprite_index++] =
                    LoadTextureFromImage(ImageFromImage(
                        loaded_image[sprites], (Rectangle){.x = x_cord * 32,
                                                           .y = y_cord * 32,
                                                           .width = 32,
                                                           .height = 32}));
            }
        }
    }
}

resource_context_t* resource_get_context() { return &ctx; }

void print_res_with_id(Camera2D *cam) {
    uint32_t x = 0;
    uint32_t y = 0;

    BeginDrawing();
    ClearBackground(WHITE);
    
    BeginMode2D(*cam);
    
    for (uint32_t i = 0; i < SPRITES_COUNT; i++) {
        DrawTexture(ctx.sprite[i], x*32, y*32, WHITE);
        if ((x % 64 == 0) && (x != 0)) {
            y++;
            x = -1;
        }
        x++;
    }

    EndMode2D();

    EndDrawing();
}
