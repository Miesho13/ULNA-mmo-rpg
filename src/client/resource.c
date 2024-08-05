#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "client_conf.h"
#include "resource.h"

static resource_context_t ctx = {};

void reso_load_image(const char *path_pattern, uint32_t img_to_load,
                     uint32_t scale) {
    assert(path_pattern);
    assert(scale > 0);
    assert(img_to_load > 0);
    assert(img_to_load <= RES_MAX_IMG_TO_LOAD);
    assert(strlen(path_pattern) < 64);

    // TODO(marcin.ryzewskii@gmail.com) maybe it shoud be good idea remove
    // this from stack inicialzation to data segment or heap.

    Image img_tmp_buffer[RES_MAX_IMG_TO_LOAD] = {};
    char tmp_path_buff[64] = {};
    for (uint32_t loaded = 0; loaded < img_to_load; loaded++) {
        sprintf(tmp_path_buff, path_pattern, loaded);
        img_tmp_buffer[loaded] = LoadImage(tmp_path_buff);
        ImageResize(&img_tmp_buffer[loaded], img_tmp_buffer[loaded].width*scale, 
            img_tmp_buffer[loaded].height*scale);
    }
    
    ctx.scale = scale;
    ctx.sprite_count = 0;
    for (uint32_t sprite_id = 0; sprite_id < RES_MAX_IMG_TO_LOAD; sprite_id++) {
        for (uint32_t y_cord = 0; y_cord < 12; y_cord++) {
            for (uint32_t x_cord = 0; x_cord < 12; x_cord++) {
                ctx.img_sprite[ctx.sprite_count++] = ImageFromImage(
                    img_tmp_buffer[sprite_id],
                    (Rectangle){x_cord * 32 * scale, y_cord * 32 * scale,
                                32 * scale, 32 * scale});
            }
        }
    }

    for (uint32_t load_sprite = 0; load_sprite < ctx.sprite_count;
         load_sprite++) {
        ctx.text_sprite[load_sprite] =
            LoadTextureFromImage(ctx.img_sprite[load_sprite]);
    }

    for (uint32_t unloaded = 0; unloaded < img_to_load; unloaded++) {
        UnloadImage(img_tmp_buffer[unloaded]);
    }
}

res_ctx_h resource_get_context() { return &ctx; }
