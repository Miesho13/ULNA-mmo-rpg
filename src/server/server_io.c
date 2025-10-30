#include "server_client_io.h"
#include "server_io.h"
#include "common.h"
#include "core.h"
#include "fix_stack.h"
#include "world_cfg.h"

#include <string.h>

void hello_user(core *CORE, cnet_message_t *msg) {
    CORE->register_people++;
    register_respone_t req = {
        .head = HELLO_OK,
        .id = CORE->register_people,
    };

    // NOTE: we don't support change port/IP in one session.
    //
    CORE->connection[CORE->register_people].recv_sock   = msg->recv_sock; 
    CORE->connection[CORE->register_people].address_len = msg->address_len;
    strcpy(CORE->connection[CORE->register_people].host, msg->host);
    strcpy(CORE->connection[CORE->register_people].port, msg->port);


    server_send(&req, sizeof(register_respone_t), 
                &msg->recv_sock, msg->address_len);

    LOG(COMMON_LOG_INFO, "REGISTER %d %s:%s", CORE->register_people, msg->host, msg->port);
}

static v2_i32 prv_get_absolut_posytion(v2_i32 player_pose, v2_i32 action_pose,
                                       uint32_t map_height, uint32_t map_wigth) {
    COMMON_NOT_IMPL_YET();
    return (v2_i32){0, 0};
}

void update_from_user(core *CORE, cnet_message_t *msg) {
    update_request_t *update = (update_request_t*)msg->data;
    
    CORE->users_update.dpos[update->id].dx = update->dpos.dx;
    CORE->users_update.dpos[update->id].dy = update->dpos.dy;

    CORE->users_update.incomming_events[update->id] = update->event;
    if (update->event.action != EV_NONE) {
        printf("player_id: %d action %d\n", update->id, update->event.action);
    }

    // A - > B 
    // server(A - > B) 
    // send_for_rest(A - > B)


    // ACTOR (x,y)
    // DEF: ACTOR_LOCATION as squer of (W, H)
    // 
    // GET LOCATION
    
    fix_stack_push_int32(&CORE->users_update.update_id_stack, update->id);
}
