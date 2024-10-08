#include <string.h>
#include "player.h"

void player_init(player_ctx_t *ctx) {

}


void player_move(player_ctx_t *ctx, direction_t dir) {
    switch(dir) {
        case DIRECTION_NORTH:  
            ctx->posytion.y += 1;
            break;

        case DIRECTION_SOUTH:  
            ctx->posytion.y -= 1;
            break;

        case DIRECTION_EAST:  
            ctx->posytion.x -= 1;
            break;

        case DIRECTION_WEST:  
            ctx->posytion.x += 1;
            break;

        case DIRECTION_NORTHEAST:  
            ctx->posytion.x -= 1;
            ctx->posytion.y += 1;
            break;

        case DIRECTION_NORTHWEST:  
            ctx->posytion.x += 1;
            ctx->posytion.y += 1;
            break;

        case DIRECTION_SOUTHEAST:  
            ctx->posytion.x -= 1;
            ctx->posytion.y -= 1;
            break;

        case DIRECTION_SOUTHWEST:  
            ctx->posytion.x += 1;
            ctx->posytion.y -= 1;
            break;

        default:
            // Do not change possytion
            break;
    }
}

