#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "resource.h"

static void load_sprite_sheet(Image *sprite_sheet, const char *pattern,
                              uint32_t to_load, uint32_t scale) {
    char sprite_sheet_path[64] = {0};
    for (uint32_t loaded = 0; loaded < to_load; loaded++) {
        sprintf(sprite_sheet_path, pattern, loaded);
        sprite_sheet[loaded] = LoadImage(sprite_sheet_path);
    }
}

void resource_load_vram(resource_texture_t *text_ctx, const char *path_pattern,
                        uint32_t sprite_sheet_to_load, uint32_t scale) {

    assert(path_pattern);
    assert(scale > 0);
    assert(sprite_sheet_to_load > 0);
    assert(strlen(path_pattern) < 64);

    Image *sprite_sheet_img =
        (Image *)malloc(sizeof(Image) * sprite_sheet_to_load);

    load_sprite_sheet(sprite_sheet_img, path_pattern, sprite_sheet_to_load,
                      scale);

    Image *sprite_img = (Image*)malloc(
            sizeof(Image)*RES_SPRITE_IN_SHEET*sprite_sheet_to_load);
    
    uint32_t sprite_id = 0;
    for (   uint32_t sprite_sheet_id = 0; 
            sprite_sheet_id < sprite_sheet_to_load; 
            sprite_sheet_id++ ) {
        
        int x = 0;
        int y = 0;
        for (uint32_t sprite_per_sheet = 0;
             sprite_per_sheet < RES_SPRITE_IN_SHEET; 
             sprite_per_sheet++) {

            sprite_img[sprite_id] = ImageFromImage(
                sprite_sheet_img[sprite_sheet_id],
                (Rectangle){
                    .x =x*RES_SPRITE_W, 
                    .y =y*RES_SPRITE_H, 
                    .width = RES_SPRITE_W, 
                    .height = RES_SPRITE_H});
            
            ImageResize(&sprite_img[sprite_id], sprite_img[sprite_id].width*scale,
                        sprite_img[sprite_id].height*scale);
            sprite_id++;
            x++;
            if (x % RES_SPRITE_IN_ROW == 0) {
               y++; 
               x = 0;
            }
        }
    }
    sprite_id = 0;

    text_ctx->text = (Texture2D*)malloc(
            sizeof(Texture2D)*RES_SPRITE_IN_SHEET*sprite_sheet_to_load);
    text_ctx->size = RES_SPRITE_IN_SHEET*sprite_sheet_to_load;
    text_ctx->scale = scale; 

    for (uint32_t sprite_id = 0; 
         sprite_id < RES_SPRITE_IN_SHEET*sprite_sheet_to_load; 
         sprite_id++) {
        printf("texture: %d\n", sprite_id);
        text_ctx->text[sprite_id] = LoadTextureFromImage(sprite_img[sprite_id]);
    }
    
    for (uint32_t sprite_id = 0; sprite_id < RES_SPRITE_IN_SHEET*sprite_sheet_to_load; sprite_id++) {
        printf("Image: %d\n", sprite_id);
        UnloadImage(sprite_img[sprite_id]);
    }

    for (uint32_t sprite_id = 0; sprite_id < sprite_sheet_to_load; sprite_id++) {
        UnloadImage(sprite_sheet_img[sprite_id]);
    }

    free(sprite_img);
    free(sprite_sheet_img);
}

void resource_free_vram(resource_texture_t *text_ctx) {
    for (uint32_t text = 0; text < text_ctx->size; text++) {
        UnloadTexture(text_ctx->text[text]);
    }
    free(text_ctx->text);
}

