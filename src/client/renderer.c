#include "renderer.h"
#include "sprite_data.h"
#include <stdio.h>


static inline uint32_t prv_get_sprite_buffer_size(sprite_loader_path_t *sheet_data) {
    return (sheet_data->sheet_height/sheet_data->sprite_height)*
            (sheet_data->sheet_width/sheet_data->sprite_width)*
            sheet_data->sheet_to_load;
}

static Image* prv_load_sheet(sprite_loader_path_t *sheet_data) {

    Image *tmp_sheet = (Image*)calloc(sheet_data->sheet_to_load, sizeof(*tmp_sheet));

    for (uint32_t image_index = 0; image_index < sheet_data->sheet_to_load; image_index++) {
        char path_tmp[64] = {0};
        sprintf(path_tmp, "%s/%s", sheet_data->sheet_path, sheet_data->sheet_name[image_index]);
        tmp_sheet[image_index] = LoadImage(path_tmp);
    }

    return tmp_sheet;
}

static Image* prv_generate_image_buffer(sprite_loader_path_t *sheet_data, Image *tmp_sheet, size_t sprite_count) {

    Image *image_buffer = calloc((sprite_count), sizeof(*image_buffer));

    uint32_t sprite_index = 0;
    for (uint32_t sheet_index = 0; sheet_index < sheet_data->sheet_to_load; sheet_index++) {
    for (uint32_t sprite_off_y = 0; sprite_off_y < sheet_data->sheet_height/sheet_data->sprite_height; sprite_off_y++) {
    for (uint32_t sprite_off_x = 0; sprite_off_x < sheet_data->sheet_width/sheet_data->sprite_width; sprite_off_x++) {
        image_buffer[sprite_index++] = ImageFromImage(
            tmp_sheet[sheet_index],
            (Rectangle){
                sprite_off_x*sheet_data->sprite_width,
                sprite_off_y*sheet_data->sprite_height,
                sheet_data->sprite_width,
                sheet_data->sprite_height
        });
    }}}

    return image_buffer;
}

void renderer_init(renderer_ctx_t *rctx, sprite_loader_path_t *sheet_data, uint32_t scale) {

    Image *tmp_sheet = prv_load_sheet(sheet_data);

    rctx->image_buffer_size = prv_get_sprite_buffer_size(sheet_data);
    rctx->image_buffer = prv_generate_image_buffer(sheet_data, tmp_sheet, rctx->image_buffer_size);

    for (uint32_t image_index = 0; image_index < sheet_data->sheet_to_load; image_index++) {
        UnloadImage(tmp_sheet[image_index]);
    }
    free(tmp_sheet);
}
