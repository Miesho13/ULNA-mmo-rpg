#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

#include "../raylib_inc/raylib.h"


const int screenWidth = 1980;
const int screenHeight = 1080;

void init_game(void) {
    InitWindow(
        screenWidth, 
        screenHeight, 
        "tibia game"
    );
    SetTargetFPS(60); 
}  

Image loaded_image[30] = {0};
Texture2D texture_v[144 * 30] = {0};
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

void draw_ui() {

}

void draw_game() {
    BeginDrawing();
    uint32_t row = 0;
    uint32_t colum = 0;
    for (uint8_t drawid = 0; drawid < 144; drawid++) { 
        DrawTexture(texture_v[drawid], 32*colum++, row, WHITE);
        if (drawid % 10 == 0 && drawid != 0) {
            colum = 0;
            row += 32;
        }
    }
    EndDrawing();
}
 
void draw_frame() {
    draw_ui();
    draw_game(); 
}

int main(void) {
    init_game();
    load_maps_texture();
    while (!WindowShouldClose()) {
        // Take user input
        // Update game state 
        // Draw shit

        draw_frame();
    }
    CloseWindow();        
    return 0;
}

