#include "renderer.h"
#include "../platform/platform.h"
#include "client_config.h"

render_err render_load_sprite_from_plain(render_sprite_vector *sprite_vector, const char *path, 
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

 
