#include "renderer.h"
#include "raylib.h"
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

static Texture* prv_load_game(renderer_ctx_t *rctx) {

    Texture *text_buffer = calloc((rctx->text_buffer_size), sizeof(*text_buffer));

    for (uint32_t sprite_index = 0; sprite_index  < rctx->text_buffer_size; sprite_index++) {
        text_buffer[sprite_index] = LoadTextureFromImage(rctx->image_buffer[sprite_index]);
    }

    return text_buffer;
}

static void prv_scale_sprite(renderer_ctx_t *rctx, double scale) {
    rctx->scale = scale;
    for (uint32_t image_index = 0; image_index < rctx->image_buffer_size; image_index++) {
        ImageResize(&rctx->image_buffer[image_index], rctx->sprite_width, rctx->sprite_height);                                       // Resize image (Bicubic scaling algorithm)
    }
}

void renderer_init(renderer_ctx_t *rctx, sprite_loader_path_t *sheet_data, double scale) {
    Image *tmp_sheet = prv_load_sheet(sheet_data);

    rctx->sprite_height = sheet_data->sprite_height*scale;
    rctx->sprite_width = sheet_data->sprite_width*scale;
    rctx->image_buffer_size = prv_get_sprite_buffer_size(sheet_data);
    rctx->image_buffer = prv_generate_image_buffer(sheet_data, tmp_sheet, rctx->image_buffer_size);

    if (scale != 1.0f) {
        prv_scale_sprite(rctx, scale);
    }

    rctx->text_buffer_size = rctx->image_buffer_size;
    rctx->text_buffer = prv_load_game(rctx);

    for (uint32_t image_index = 0; image_index < sheet_data->sheet_to_load; image_index++) {
        UnloadImage(tmp_sheet[image_index]);
    }
    free(tmp_sheet);
}
