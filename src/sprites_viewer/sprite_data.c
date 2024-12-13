#include "sprite_data.h"

#define GAME_SPRITE_PATH "./resources"
static char *game_sprite_name[] = {
    "Sprites-0.png", "Sprites-1.png",
    "Sprites-2.png", "Sprites-3.png",
    "Sprites-4.png", "Sprites-5.png",
    "Sprites-6.png", "Sprites-7.png",
    "Sprites-8.png", "Sprites-9.png",
    "Sprites-10.png", "Sprites-11.png",
    "Sprites-12.png", "Sprites-13.png",
    "Sprites-14.png", "Sprites-15.png",
    "Sprites-16.png", "Sprites-17.png",
    "Sprites-18.png", "Sprites-19.png",
    "Sprites-20.png", "Sprites-21.png",
    "Sprites-22.png", "Sprites-23.png",
    "Sprites-24.png", "Sprites-25.png",
    "Sprites-26.png",
};

sprite_loader_path_t game_sprite_load_ctx = {
    .sheet_name = game_sprite_name,
    .sheet_width = 384,
    .sheet_height = 384,
    .sheet_path = GAME_SPRITE_PATH,
    .sheet_to_load = sizeof(game_sprite_name)/sizeof(char*),
    .sprite_width = 32,
    .sprite_height = 32,
};
