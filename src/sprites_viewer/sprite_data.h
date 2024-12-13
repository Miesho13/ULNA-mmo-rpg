#ifndef __SPRITE_PATH__
#define __SPRITE_PATH__

#include <stdlib.h>

typedef struct _sprite_loader_path_t {
    char **sheet_name;
    char *sheet_path;
    size_t sheet_height;
    size_t sheet_width;
    size_t sheet_to_load;
    size_t sprite_width;
    size_t sprite_height;
} sprite_loader_path_t;

extern sprite_loader_path_t game_sprite_load_ctx;
extern sprite_loader_path_t ui_rend;

#endif
