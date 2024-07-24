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
Texture2D texture_v[30 * (324)] = {0};
void load_maps_texture() {
    char path_buff[124] = {0};
    for (uint8_t imgindex = 0; imgindex < 30; imgindex++) {
        sprintf(path_buff, "./resources/7.1/Sprites-%d.png", imgindex);
        loaded_image[imgindex]  = LoadImage(path_buff);
    }
    
    // 32 x 32 
    // 384 x 384
}

void draw_ui() {

}

void draw_game() {
    for (uint8_t drawid = 0; drawid < 30; drawid++) { 
        Texture2D text = LoadTextureFromImage(loaded_image[drawid]);

        ClearBackground(DARKGRAY);
        BeginDrawing();
        DrawTexture(text, screenWidth/2, screenHeight/2, WHITE);
        EndDrawing();
    }
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
        // Draw sheet

        draw_frame();
    }
    CloseWindow();        
    return 0;
}

