#ifndef CORE_H
#define CORE_H

#include "server_cfg.h"
#include "server.h"
#include "server_client_io.h"
#include "common.h"
#include "time_bench.h"
#include "world_cfg.h"
#include "../common/fix_stack.h"


typedef struct {
    uint16_t register_people;
    uint16_t reg_player_id[MAX_PLAYER_COUNT];

    event_t event[WORLD_MAP]; 

    struct {
        char host[NI_MAXHOST];
        char port[NI_MAXSERV];
        struct sockaddr recv_sock;
        socklen_t address_len; 
    } connection[MAX_PLAYER_COUNT];

    struct {
        v2_i32   pos[MAX_PLAYER_COUNT];
        uint8_t  npc_map[WORLD_MAP]; 
        uint16_t player_map[WORLD_MAP]; 
    } world_state;

    struct {
        struct {
            int8_t dx;
            int8_t dy;
        } dpos[MAX_PLAYER_COUNT];

        uint32_t         id_stack_buffer[MAX_PLAYER_COUNT];
        update_respone_t update_respone[MAX_PLAYER_COUNT];
        fix_stack update_id_stack;
    } users_update;

    // server timers
    common_timert server_colection_data;
} core;

void core_init(void);
int core_run(void);

#endif
