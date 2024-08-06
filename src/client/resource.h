#ifndef __RESOURCE_H__
#define __RESOURCE_H__

#include <stdint.h>
#include "raylib.h"

#define RES_MAX_IMG_TO_LOAD 30
#define RES_SPRITE_PER_IMG 144
#define RES_MAX_SPRITES_COUNT (RES_MAX_IMG_TO_LOAD * RES_SPRITE_PER_IMG)


typedef struct {
    Texture2D text_sprite[RES_MAX_SPRITES_COUNT];
    Image img_sprite[RES_MAX_SPRITES_COUNT];
    uint32_t scale;
    uint32_t sprite_count;

} resource_context_t;
typedef resource_context_t* res_ctx_h;
typedef uint32_t resource_id_t;

void reso_load_image(const char *path_pattern, uint32_t img_to_load,
                     uint32_t scale); 
res_ctx_h resource_get_context();

#endif
