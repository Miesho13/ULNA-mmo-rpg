#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "raylib.h"
#include "../common/common_strcut.h"
#include "resource.h"

typedef enum  {
    DIRECTION_NONE,
    DIRECTION_NORTH,
    DIRECTION_SOUTH,
    DIRECTION_EAST,
    DIRECTION_WEST,
    DIRECTION_NORTHEAST,
    DIRECTION_NORTHWEST,
    DIRECTION_SOUTHEAST,
    DIRECTION_SOUTHWEST,

} direction_t;

typedef struct {
    resource_id_t data[8];
    resource_id_t begin;
    resource_id_t end;

} player_animation;

typedef struct {
    common_int32_vec posytion;
    player_animation animation_ctx;

} player_ctx_t;

void player_init(player_ctx_t *ctx);
void player_move(player_ctx_t *ctx, direction_t dir);

#endif
