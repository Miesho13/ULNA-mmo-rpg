#include "core.h"
#include "server_cfg.h"
#include "world_cfg.h"

#include <string.h>

static inline int prv_update_new_pos(core *CORE, uint16_t player_id, 
                                    int old_x, int old_y, 
                                    int new_x, int new_y) {
    if (new_x < 0) { return 1; }
    if (new_y < 0) { return 1; }

    if (CORE->world_state.player_map[new_y*WORLD_MAP_W + new_x].posytion != 0) {
        return 1;
    }
    
    CORE->world_state.player_map[old_y*WORLD_MAP_W + old_x].posytion  = 0;
    CORE->world_state.player_map[new_y*WORLD_MAP_W + new_x].posytion = player_id;

    CORE->world_state.pos[player_id].x = new_x;
    CORE->world_state.pos[player_id].y = new_y;

    return 0;
}

static void prv_extract_clamped(uint16_t id, const map_grid *grid, 
                               int W, int H, int x, 
                               int y, map_grid out[WORLD_LOCAL_BUFFER]) {
    assert(W >= WORLD_LOCAL_W && H >= WORLD_LOCAL_H);

    const int half = WORLD_LOCAL_W / 2;
    int x0 = x - half;
    int y0 = y - half;

    if (x0 < 0)        x0 = 0;
    if (y0 < 0)        y0 = 0;
    if (x0 > W - WORLD_LOCAL_W)  x0 = W - WORLD_LOCAL_W;
    if (y0 > H - WORLD_LOCAL_H)  y0 = H - WORLD_LOCAL_H;

    for (int r = 0; r < WORLD_LOCAL_W; ++r) {
        const map_grid *src = grid + (y0 + r) * W + x0;
        map_grid *dst       = out  + r * WORLD_LOCAL_W;
        memcpy(dst, src, sizeof(map_grid)*WORLD_LOCAL_W);
    }

    int gx = x - x0;
    int gy = y - y0;
    if (gx >= 0 && gx < WORLD_LOCAL_W && gy >= 0 && gy < WORLD_LOCAL_W) {
        out[gy * WORLD_LOCAL_W + gx].posytion = id;
    }
}

void update_position(core *CORE, uint32_t player_id) {
    prv_update_new_pos(
        CORE, player_id, 
        CORE->world_state.pos[player_id].x, CORE->world_state.pos[player_id].y,
        CORE->world_state.pos[player_id].x + CORE->users_update.dpos[player_id].dx,
        CORE->world_state.pos[player_id].y + CORE->users_update.dpos[player_id].dy
    );

    map_grid local_grid[WORLD_LOCAL_BUFFER] = {0};

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

void update_claster(core *CORE, uint32_t player_id) {
//    map_grid local_grid[WORLD_LOCAL_BUFFER] = {0};
//    prv_extract_clamped(
//        player_id, CORE->world_state.player_map,
//        WORLD_MAP_W, WORLD_MAP_H, 
//        CORE->world_state.pos[player_id].x,
//        CORE->world_state.pos[player_id].y,
//        local_grid
//    );
//
//    CORE->world_state.claster[player_id] = 0;
//
//    for (int idx = 0; idx < WORLD_LOCAL_BUFFER; idx++) {
//        if (local_grid[idx].posytion == 0 || local_grid[idx].posytion == player_id) {
//            continue;
//        }
//
//        if (local_grid[idx].claster == 0) {
//            continue; 
//        }
//        
//        CORE->world_state.claster[player_id] = local_grid[idx].claster;
//        break;
//    }
//
//    if (CORE->world_state.claster[player_id] == 0) {
//        CORE->world_state.claster[player_id] = ++CORE->world_state.claster_count;
//    }

    CORE->world_state.claster[player_id] = 1;
}

void update_events(core *CORE, uint16_t player_id) {
    event_t new_event   = CORE->users_update.incomming_events[player_id];
    new_event.player_id = player_id;
    if (new_event.action == 0) {
        return;
    }

    uint16_t claster    = CORE->world_state.claster[player_id];
    uint8_t event_count = CORE->clasters[claster].event_count;


    CORE->clasters[claster].events[event_count] = new_event;
    CORE->clasters[claster].event_count++;
}


void epilog_update(core *CORE, uint32_t player_id) {
    CORE->users_update.update_respone[player_id].head = UPDATE_OK;  
}


