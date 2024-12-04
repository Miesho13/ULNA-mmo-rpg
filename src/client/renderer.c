#include "renderer.h"
#include <stdio.h>


#define RESOURCE_PATH "./resources/"


static const uint32_t IMAGE_COUNT = ((384 / 32) * (384 / 32)) * 30;

static Image* prv_load_image_sheet(renderer_ctx_t *rctx, const char *pattern, uint32_t sheet_count) {
    
    char tmp[124] = {0};
    for (uint32_t sheet_id = 0; sheet_id < sheet_count; sheet_id++) {
        sprintf(tmp, pattern, sheet_id);
        Image img = LoadImage(pattern);
    }

}

static Image *prv_load_image_from_sheet(
    const char *pattern, uint32_t sheet_count, 
    uint32_t img_per_sheet, 
    image_size_px partial_size) {

}

void renderer_load_text(renderer_ctx_t *rctx) {

}

void renderer_free_text(renderer_ctx_t *rctx) {

}

void renderer_init(renderer_ctx_t *rctx, const char **pattern, 
                   uint32_t sheet_count, uint32_t scale) {
    Image *tmp_sheet = (Image*)calloc(sheet_count, sizeof(*tmp_sheet));
    for (uint32_t image_index = 0; image_index < sheet_count; image_index++) {
        char path_tmp[64] = "";
        sprintf(path_tmp, "./resources/%s", pattern[image_index]);
        tmp_sheet[image_index] = LoadImage(path_tmp);
    }
     
    rctx->image_buffer = calloc(IMAGE_COUNT, sizeof(Image));
    
    uint32_t sprite_index = 0;
    for (uint32_t sheet_index = 0; sheet_index < 1; sheet_index++) {
    for (uint32_t sprite_off_y = 0; sprite_off_y < 12; sprite_off_y++) {
    for (uint32_t sprite_off_x = 0; sprite_off_x < 12; sprite_off_x++) {
        rctx->image_buffer[sprite_index++] = ImageFromImage(
            tmp_sheet[sheet_index], 
            (Rectangle){sprite_off_x*32, sprite_off_y*32, 32, 32});
    }}}

    free(tmp_sheet);
}


