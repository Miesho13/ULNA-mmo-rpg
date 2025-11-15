
#include "sprite.h"

render_err render_load_sprite_from_plain(sprite_context *sprite_vector, const char *path, 
                                         v2_i32 sprite_size, float scale) {
    assert(path && "path cant be NULL");

    const platform_img plain = platform_load_img(path);
    const uint32_t sprite_coutn = (plain.width/sprite_size.x) * (plain.height/sprite_size.y);

    if (sprite_coutn < 1) { return RENDER_ERR; }
    
    const int width = sprite_size.x;
    const int height = sprite_size.y; 

    sprite_vector->scale = scale;

    int x = 0; int y = 0; 
    for (uint32_t sprite = 0; sprite < sprite_coutn; sprite++) {
        if (sprite_vector->sprite_count >= RENDER_MAX_SPRITE_SIZE) {
            return RENDER_ERR;
        }

        platform_img       *local_img = &sprite_vector->img[sprite_vector->sprite_count];
        platform_sprite *local_sprite = &sprite_vector->sprite[sprite_vector->sprite_count];

        *local_img = platform_load_img_from_image(plain, x, y, width, height);
        platform_img_resize(local_img, sprite_size.x*scale, sprite_size.y*scale);
        *local_sprite = platform_load_to_gpu(local_img);

        sprite_vector->sprite_count++;

        x += width;
        if (x >= plain.width) {
            x = 0;
            y += height;
        }

        if (y >= plain.width) {
            break;
        }

    }

    return RENDER_OK; 
}

void load_sprite(sprite_context *ctx_sprite) {
    const char tmp[255] = {0};
    for (int i = 0; i < 30; i++) {
        sprintf((char*)tmp, "./../resources/7.1/Sprites-%d.png", i);

        render_load_sprite_from_plain(
            ctx_sprite, tmp,
            (v2_i32){.x = 32, .y = 32}, 1 
        );
    }
}

void render_sprite(sprite_context *ctx, int id, int x, int y) {
    platform_render(&ctx->sprite[id], x, y, 0xffffffff);
}

