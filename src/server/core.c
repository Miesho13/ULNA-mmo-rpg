#include "core.h"

#include "server_cfg.h"
#include "server.h"
#include "server_client_io.h"
#include "server_io.h"
#include "common.h"
#include "time_bench.h"
#include "world_update.h"
#include "../common/fix_stack.h"

#include <stdint.h>
#include <string.h>

typedef enum {
    CORE_OK,
    CORE_ERR,

} CORE_RETURN;

static core CORE;

void print_startup_info(void) {
    printf("sizeof(core) = %ldMB\n", sizeof(core)/1024/1024);
}

void handle_recv(cnet_message_t *msg) {
    switch (msg->data[0]) {
        case HELLO: { 
            hello_user(&CORE, msg);
            break;
        }

        case UPDATE: {  
            update_from_user(&CORE, msg);
            break;
        }

        case GOOD_BYE: {  
            break;
        }

        default: {  
            break;
        }
    }
}

static inline void send_update_respone(uint32_t player_id) {
    update_respone_t *update_respone = &CORE.users_update.update_respone[player_id];
    
    printf("player %d\n 1: update_respone (%d %d)\n", player_id, update_respone->pos.x, update_respone->pos.y);

    memcpy(
        update_respone->events, 
        CORE.clasters[0].events, 
        sizeof(update_respone->events)*CORE.clasters[0].event_count
    );

    printf("2: update_respone (%d %d)\n", update_respone->pos.x, update_respone->pos.y);


    server_send(
        update_respone, 
        sizeof(*update_respone),
        &CORE.connection[player_id].recv_sock,
        CORE.connection[player_id].address_len
    );

    LOG_DEBUG( 
        COMMON_LOG_INFO, 
        "SNED TO: (%s:%s) %x", 
        CORE.connection[player_id].host, 
        CORE.connection[player_id].port,
        CORE.users_update.update_respone[player_id].head
    );
}

static inline void collect_data(void) {
    time_reset(&CORE.server_colection_data, SERVER_COLLECTION_DATA_US);
    do {
        server_step();  
    } while (!time_elapsed(&CORE.server_colection_data));
}

static inline void update_server_state(void) {
    fix_stack *update_stack = &CORE.users_update.update_id_stack;
    
    fix_stack send_stack;
    uint32_t tmp_send_buffer[255];
    fix_stack_init(
        &send_stack,
        tmp_send_buffer,
        sizeof(tmp_send_buffer) / sizeof(uint32_t)
    );
        
    while (fix_stack_count(update_stack) != 0) {
        uint32_t player_id = fix_stack_get_int32(update_stack);

        update_position(&CORE, player_id);
        update_claster(&CORE, player_id);
        update_events(&CORE, player_id);

        // NOTE: This function need to call befre send update respone
        // 
 
        fix_stack_push_int32(&send_stack, player_id);
        fix_stack_pop_int32(update_stack);
    }

    // SEND ALL UPDATEING DATA FOR CLINETS
    while (fix_stack_count(&send_stack) != 0) {
        uint32_t player_id = fix_stack_get_int32(&send_stack);

        epilog_update(&CORE, player_id);
        send_update_respone(player_id);

        fix_stack_pop_int32(&send_stack);
    }
}

static inline int init(void) {
    // Init stak for player's ID rdy to update
    fix_stack_init(
        &CORE.users_update.update_id_stack, 
        CORE.users_update.id_stack_buffer,
        sizeof(CORE.users_update.id_stack_buffer) / sizeof(uint32_t)
    );

    if (server_init(handle_recv) == SERVER_ERR) {
        return CORE_ERR;
    }

    return CORE_OK;
}

int core_run(void) {
    print_startup_info();

    int ret = init();
    if (ret != CORE_OK) {
        return 420;
    }

    while (1)  {
        collect_data();
        update_server_state();
    }
}

