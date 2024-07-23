#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "assert.h"

#include "../raylib_inc/raylib.h"


Image spriteImg;
Texture2D sprite;
void init_game(void) {
    const int screenWidth = 1980;
    const int screenHeight = 1080;
    InitWindow(
        screenWidth, 
        screenHeight, 
        "tibia game"
    );
    SetTargetFPS(60); 

    spriteImg = LoadImage("./resources/7.1/Sprites-28.png");
    assert(spriteImg.data != NULL); 
    ImageRotate(&spriteImg, 90);
    sprite = LoadTextureFromImage(spriteImg);
}  

// 1. Draw maps
// 2. Draw maps obj
// 3. Draw NPS
// 4. Draw Player 

void load_map_texture() {
           
}

void draw_frame(void) {
    // draw maps
    // draw obj
    // draw NPC
    // draw player
    

}

int main(void) {
    init_game();
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_B) == true) {
            printf("B!\n");
        }
    
        draw_frame();

    }
    CloseWindow();        
    return 0;
}

