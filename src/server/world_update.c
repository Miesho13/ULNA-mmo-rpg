#include "core.h"
#include "server_cfg.h"
#include "world_cfg.h"

#include <string.h>

static inline int prv_update_new_pos(core *CORE, uint16_t player_id, 
                                    int old_x, int old_y, 
                                    int new_x, int new_y) {
    if (new_x < 0) { return 1; }
    if (new_y < 0) { return 1; }

    if (CORE->world_state.player_map[new_y*WORLD_MAP_W + new_x] != 0) {
        return 1;
    }
    
    CORE->world_state.player_map[old_y*WORLD_MAP_W + old_x]  = 0;
    CORE->world_state.player_map[new_y*WORLD_MAP_W + new_x]  = player_id;

    CORE->world_state.pos[player_id].x = new_x;
    CORE->world_state.pos[player_id].y = new_y;

    return 0;
}

static void prv_extract_clamped(uint16_t id, const uint16_t *grid, 
                               int W, int H, int x, 
                               int y, uint16_t out[WORLD_LOCAL_BUFFER]) {
    assert(W >= WORLD_LOCAL_W && H >= WORLD_LOCAL_H);

    const int half = WORLD_LOCAL_W / 2;
    int x0 = x - half;
    int y0 = y - half;

    if (x0 < 0)        x0 = 0;
    if (y0 < 0)        y0 = 0;
    if (x0 > W - WORLD_LOCAL_W)  x0 = W - WORLD_LOCAL_W;
    if (y0 > H - WORLD_LOCAL_H)  y0 = H - WORLD_LOCAL_H;

    for (int r = 0; r < WORLD_LOCAL_W; ++r) {
        const uint16_t *src = grid + (y0 + r) * W + x0;
        uint16_t *dst       = out  + r * WORLD_LOCAL_W;
        memcpy(dst, src, sizeof(uint16_t)*WORLD_LOCAL_W);
    }

    int gx = x - x0;
    int gy = y - y0;
    if (gx >= 0 && gx < WORLD_LOCAL_W && gy >= 0 && gy < WORLD_LOCAL_W) {
        out[gy * WORLD_LOCAL_W + gx] = id;
    }
}

void update_position(core *CORE, uint32_t player_id) {
    prv_update_new_pos(
        CORE, player_id, 
        CORE->world_state.pos[player_id].x, CORE->world_state.pos[player_id].y,
        CORE->world_state.pos[player_id].x + CORE->users_update.dpos[player_id].dx,
        CORE->world_state.pos[player_id].y + CORE->users_update.dpos[player_id].dy
    );

    prv_extract_clamped(
        player_id, CORE->world_state.player_map,
        WORLD_MAP_W, WORLD_MAP_H, 
        CORE->world_state.pos[player_id].x,
        CORE->world_state.pos[player_id].y,
        CORE->users_update.update_respone[player_id].player_map
    );

    CORE->users_update.update_respone[player_id].pos.x = CORE->world_state.pos[player_id].x;
    CORE->users_update.update_respone[player_id].pos.y = CORE->world_state.pos[player_id].y;
}

void epilog_update(core *CORE, uint32_t player_id) {
    CORE->users_update.update_respone[player_id].head = UPDATE_OK;  
}


