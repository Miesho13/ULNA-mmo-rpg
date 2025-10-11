#include "server_client_io.h"
#include "server_io.h"
#include "common.h"
#include "core.h"
#include "fix_stack.h"

void hello_user(core *CORE, cnet_message_t *msg) {
    CORE->reg_ppl++;
    register_respone_t req = {
        .head = HELLO_OK,
        .id = CORE->reg_ppl,
    };

    server_send(&req, sizeof(register_respone_t), 
                &msg->recv_sock, msg->address_len);

    LOG(COMMON_LOG_INFO, "REGISTER %d %s:%s", CORE->reg_ppl, msg->host, msg->port);
}

static int prv_set_dpos(core *CORE, uint16_t id, int old_x, int old_y, int new_x, int new_y) {
    if (new_x < 0) { return 1; }
    if (new_y < 0) { return 1; }

    CORE->update_form_user.player_map[old_y * WORD_MAP_W + old_x]  = 0;
    CORE->update_form_user.player_map[new_y * WORD_MAP_W + new_x]  = id;
    
    return 0;
}

void update_from_user(core *CORE, cnet_message_t *msg) {
    update_request_t *update = (update_request_t*)msg->data;
    
    CORE->update_form_user.dpos[update->id].dx = update->dpos.dx;
    CORE->update_form_user.dpos[update->id].dy = update->dpos.dy;

    fix_stack_push_int32(&CORE->update_form_user.update_id_stack, update->id);
}
