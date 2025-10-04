#include "core.h"

#include "server_cfg.h"
#include "server.h"
#include "server_client_io.h"
#include "common.h"

#include <stdint.h>
#include <string.h>

typedef enum {
    CORE_OK,
    CORE_ERR,

} CORE_RETURN;

#define WIN 11 
#define WORD_MAP (255 * 255)
#define WORD_MAP_H (255)
#define WORD_MAP_W (255)

typedef struct {
    int x;
    int y;
} Pos_t;

static struct {
    uint16_t reg_ppl;
    uint16_t reg_player_id[MAX_PLAYER_COUNT];
    Pos_t pos[MAX_PLAYER_COUNT];

    uint16_t player_map[WORD_MAP]; 
    uint8_t npc_map[WORD_MAP]; 
} CORE;

void extract8x8_clamped(uint16_t id, const uint16_t *grid, 
                        int W, int H, int x, 
                        int y, uint16_t out[WIN*WIN]) {
    assert(W >= WIN && H >= WIN);

    const int half = WIN / 2;
    int x0 = x - half;
    int y0 = y - half;

    if (x0 < 0)        x0 = 0;
    if (y0 < 0)        y0 = 0;
    if (x0 > W - WIN)  x0 = W - WIN;
    if (y0 > H - WIN)  y0 = H - WIN;

    for (int r = 0; r < WIN; ++r) {
        const uint16_t *src = grid + (y0 + r) * W + x0;
        uint16_t *dst       = out  + r * WIN;
        memcpy(dst, src, sizeof(uint16_t)*WIN);
    }

    int gx = x - x0;
    int gy = y - y0;
    if (gx >= 0 && gx < WIN && gy >= 0 && gy < WIN) {
        out[gy * WIN + gx] = id;
    }
    
}

int new_pos(uint16_t id, int old_x, int old_y, int new_x, int new_y) {
    if (new_x < 0) { return 1; }
    if (new_y < 0) { return 1; }

    CORE.player_map[old_y*WORD_MAP_W + old_x]  = 0;
    CORE.player_map[new_y*WORD_MAP_W + new_x]  = id;
    
    return 0;
}

void eval_mov(cnet_message_t *msg) {
    event_request_t *msg_req = (event_request_t*)msg->data;

    
    int ret = new_pos(msg_req->id, CORE.pos[msg_req->id].x, CORE.pos[msg_req->id].y, 
            CORE.pos[msg_req->id].x + msg_req->dpos.dx, 
            CORE.pos[msg_req->id].y + msg_req->dpos.dy);
    
    if (ret == 0) {
        CORE.pos[msg_req->id].x += msg_req->dpos.dx;
        CORE.pos[msg_req->id].y += msg_req->dpos.dy;
    }

    update_respone_t respone = {
        .head = UPDATE,
        .pos = {
            .x = CORE.pos[msg_req->id].x,
            .y = CORE.pos[msg_req->id].y
        }
    };

    extract8x8_clamped(msg_req->id, CORE.player_map,
                       WORD_MAP_W, WORD_MAP_H,
                       CORE.pos[msg_req->id].x, CORE.pos[msg_req->id].y,
                       respone.player_map);
#if 0    
    for (int i = 0; i < 11*11; i++) {
        if (i % 11 == 0 && i != 0) {
            printf("\n");
        }
        printf("%d ", respone.player_map[i]);
    }
    printf("\n");
#endif

    server_send(&respone, sizeof(respone), &msg->recv_sock,
                msg->address_len);
}

void reg_user(cnet_message_t *msg) {
    CORE.reg_ppl++;
    register_respone_t req = {
        .head = HELLO_OK,
        .id = CORE.reg_ppl,
    };

    server_send(&req, sizeof(register_respone_t), 
                &msg->recv_sock, msg->address_len);

    LOG(LOG_INFO, "REGISTER %d %s:%s", CORE.reg_ppl, msg->host, msg->port);
}

head_t get_heder(uint8_t *data) {
    switch (data[0]) {
        case HELLO:     { return HELLO; }
        case MOVE:      { return MOVE; }
        case UPDATE:    { return UPDATE; }
        case GOOD_BYE:  { return GOOD_BYE; }
        default:    { return NONE; }
    }
}

void clear_pos(int pos_x, int pos_y) {
    CORE.player_map[pos_y*WORD_MAP_W + pos_x]  = 0;
}

void eval_good_bye(cnet_message_t *msg) {
    good_bye_request_t *msg_req = (good_bye_request_t*)msg->data;
    clear_pos(CORE.pos[msg_req->id].x, CORE.pos[msg_req->id].y);
}

void handle_rec(cnet_message_t *msg) {
    head_t header = get_heder(msg->data);
    if (header == HELLO) {
        reg_user(msg);
    }
    else if (header == UPDATE) {
        eval_mov(msg);
    }
    else if (header == GOOD_BYE) {
        eval_good_bye(msg);
    }
    else if (header == NONE){
        LOG(LOG_INFO, "RANDOM HEADER"); 
    }
}

int core_run(void) {
    memset(&CORE, 0, sizeof(CORE));

    if (server_init(handle_rec) == SERVER_ERR) {
        return CORE_ERR;
    }
    
    while (1)  {
        server_step();
    }
}

