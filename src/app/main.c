#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../raylib_inc/raylib.h"


void init_game(void) {
    const int screenWidth = 1980;
    const int screenHeight = 1080;
    InitWindow(
        screenWidth, 
        screenHeight, 
        "tibia game"
    );
    SetTargetFPS(60); 
}  


void draw_frame(void) {
    

    // 512x512   
    // 32x32
    // scums = 16x16 
    
    
    BeginDrawing();
        DrawRectangle(100.f, 100.f, 50, 50, BLUE);
    EndDrawing();
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

