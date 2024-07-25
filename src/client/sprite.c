#include <stdint.h>
#include <stdio.h>

#include "renderer.h"
#include "client_config.h"
#include "../raylib_inc/raylib.h"




void load_maps_texture() {
    char path_buff[124] = {0};
    for (uint8_t imgindex = 0; imgindex < 30; imgindex++) {
        sprintf(path_buff, "./resources/7.1/Sprites-%d.png", imgindex);
        loaded_image[imgindex]  = LoadImage(path_buff);
    }
    

    // Craete text_v
    uint32_t sprite_index = 0;
    for (uint16_t plate_index = 0; plate_index < 30; plate_index++) {
        
    }
}
