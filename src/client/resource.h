#ifndef __RESOURCE_H__
#define __RESOURCE_H__

#include <stdint.h>
#include "raylib.h"

#define RES_MAX_IMG_TO_LOAD 30
#define RES_SPRITE_PER_IMG 144
#define RES_MAX_SPRITES_COUNT (RES_MAX_IMG_TO_LOAD * RES_SPRITE_PER_IMG)

// SPRITE SHEET INFO
#define RES_SPRITE_SHEET_W (384)
#define RES_SPRITE_SHEET_H (384)
#define RES_SPRITE_H (32)
#define RES_SPRITE_W (32)
#define RES_SPRITE_IN_ROW (12)
#define RES_SPRITE_IN_COLUMN (12)
#define RES_SPRITE_IN_SHEET (RES_SPRITE_IN_COLUMN * RES_SPRITE_IN_ROW)


typedef struct {
    Texture2D *text;
    uint32_t size;
    uint32_t scale;

} resource_texture_t;

void resource_load_vram(resource_texture_t *text_ctx, const char *path_pattern,
                        uint32_t sprite_sheet_to_load, uint32_t scale);

#endif
