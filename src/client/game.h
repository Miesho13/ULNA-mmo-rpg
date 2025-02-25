#ifndef __GAME__
#define __GAME__

#include "renderer.h"

typedef struct {
    renderer_ctx_t game_renderer;

} game_context_t;

void game_frame(game_context_t *game_ctx);

#endif
