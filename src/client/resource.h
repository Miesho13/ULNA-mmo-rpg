#ifndef __RESOURCE_H__
#define __RESOURCE_H__

#include <stdint.h>
#include "raylib.h"

#define IMAGE_MAX_COUNT 30
#define SPRITE_PER_IMG 144
#define SPRITES_COUNT (SPRITE_PER_IMG * IMAGE_MAX_COUNT)

typedef struct {
    Texture2D sprite[SPRITES_COUNT];
    uint32_t sprite_count;

} resource_context_t;

void resource_init();

resource_context_t* resource_get_context();

void print_res_with_id(Camera2D *cam);

#endif
