#include <stdlib.h>

#include "server.h"
#include "common.h"
#include "server_client_io.h"
#include "server_cfg.h"

#include <string.h>

#ifdef __linux__

#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/epoll.h>

#define CNET_TX_BUFFER_MAX_SIZE (4*1024)
#define CNET_EPOLL_MAX_EVENT (10)
#define EVENT_POLL_SIZE (64)

typedef struct  {
    uint8_t data[CNET_TX_BUFFER_MAX_SIZE];
    uint32_t data_size;
    char host[NI_MAXHOST];
    char port[NI_MAXSERV];
    struct sockaddr recv_sock;
    socklen_t address_len; 
} cnet_message_t;

static struct {
    int fd; 
    int epollfd;
    struct epoll_event ev;
    struct epoll_event events[EVENT_POLL_SIZE];

} prv_server_context;

static int prv_set_non_block(void) {
    int flags = fcntl(prv_server_context.fd, F_GETFL, 0);
    if (flags == -1) {
        return -1;
    }
    return fcntl(prv_server_context.fd, F_SETFL, flags | O_NONBLOCK);
}

static int prv_setup_epoll(void) {
    prv_server_context.epollfd = epoll_create1(0);
    if (prv_server_context.epollfd < 0) { 
        return -1;
    }
    prv_server_context.ev.events = EPOLLIN;
    prv_server_context.ev.data.fd = prv_server_context.fd;

    epoll_ctl(prv_server_context.epollfd, 
        EPOLL_CTL_ADD, 
        prv_server_context.fd, 
        &prv_server_context.ev);

    return 0;
}

#define WIN 11 
#define WORD_MAP (255 * 255)
#define WORD_MAP_H (255)
#define WORD_MAP_W (255)
uint8_t word_filed[WORD_MAP] = {0};

int new_pos(int old_x, int old_y, int new_x, int new_y) {
    if (new_x < 0) { return 1; }
    if (new_y < 0) { return 1; }

    word_filed[old_y*WORD_MAP_W + old_x]  = 0;
    word_filed[new_y*WORD_MAP_W + new_x]  = 1;
    
    return 0;
}

void extract8x8_clamped(const uint8_t *grid, int W, int H, int x, int y, uint8_t out[WIN*WIN]) {
    assert(W >= WIN && H >= WIN); // musi być miejsce na pełne 8x8

    const int half = WIN / 2; // 4
    int x0 = x - half;
    int y0 = y - half;

    // "Zaciskamy" top-left tak, aby okno 8x8 nie wyszło poza mapę
    if (x0 < 0)        x0 = 0;
    if (y0 < 0)        y0 = 0;
    if (x0 > W - WIN)  x0 = W - WIN;
    if (y0 > H - WIN)  y0 = H - WIN;

    // Kopiowanie wierszami (szybko)
    for (int r = 0; r < WIN; ++r) {
        const uint8_t *src = grid + (y0 + r) * W + x0;
        uint8_t *dst       = out  + r * WIN;
        memcpy(dst, src, WIN);
    }

    int gx = x - x0;
    int gy = y - y0;
    if (gx >= 0 && gx < WIN && gy >= 0 && gy < WIN) {
        out[gy * WIN + gx] = 2;
    }
}

typedef struct {
    int x;
    int y;
} Pos_t;

static struct {
    uint32_t reg_ppl;
    uint32_t reg_player_id[MAX_PLAYER_COUNT];
    Pos_t pos[MAX_PLAYER_COUNT];
} game_state;

head_t get_heder(uint8_t *data) {
    switch (data[0]) {
        case HELLO: { return HELLO; }
        case MOVE:  { return MOVE; }
        case GOOD_BYE:  { return GOOD_BYE; }

        default:    { return NONE; }
    }
}

void reg_user(cnet_message_t *msg) {
    register_respone_t req = {
        .head = HELLO_OK,
        .id = game_state.reg_ppl++ 
    };

    sendto(prv_server_context.fd, &req, sizeof(req), 0, &msg->recv_sock, msg->address_len);
}

void eval_mov(cnet_message_t *msg) {
    event_request_t *msg_req = (event_request_t*)msg->data;

    
    int ret = new_pos(game_state.pos[msg_req->id].x, game_state.pos[msg_req->id].y, 
            game_state.pos[msg_req->id].x + msg_req->dpos.dx, 
            game_state.pos[msg_req->id].y + msg_req->dpos.dy);
    
    if (ret == 0) {
        game_state.pos[msg_req->id].x += msg_req->dpos.dx;
        game_state.pos[msg_req->id].y += msg_req->dpos.dy;
    }

    event_respone_t respone = {
        .head = EVENT_OK,
        .pos = {
            .x = game_state.pos[msg_req->id].x,
            .y = game_state.pos[msg_req->id].y
        }
    };

    extract8x8_clamped(word_filed, WORD_MAP_W, WORD_MAP_H, game_state.pos[msg_req->id].x, 
            game_state.pos[msg_req->id].y, respone.players);

    sendto(prv_server_context.fd, &respone, 
            sizeof(respone), 0, &msg->recv_sock, msg->address_len);
}

void clear_pos(int pos_x, int pos_y) {
    word_filed[pos_y*WORD_MAP_W + pos_x]  = 0;
}

void eval_good_bye(cnet_message_t *msg) {
    good_bye_request_t *msg_req = (good_bye_request_t*)msg->data;
    clear_pos(game_state.pos[msg_req->id].x, game_state.pos[msg_req->id].y);
}

static void recv_callback(cnet_message_t *msg) {
    int header = get_heder(msg->data);
    if (header == HELLO) {
        reg_user(msg);
        LOG(INFO, "new reg: id:%d %s:%s", game_state.reg_ppl - 1, msg->host, msg->port);
    }
    else if (header == MOVE) {
        eval_mov(msg);
    }
    else if (header == GOOD_BYE) {
        eval_good_bye(msg);
    }
    else if (header == NONE){
        LOG(INFO, "RANDOM HEADER"); 
    }
}

static inline int prv_udp_step(void) {
    int event_count = epoll_wait(prv_server_context.epollfd, prv_server_context.events, EVENT_POLL_SIZE, -1);
    if (event_count < 0) {
        perror("epoll_wait");
        return -1;  
    }
    
    for (int event_id = 0; event_id < event_count; event_id++) {
        uint32_t event_handler = prv_server_context.events[event_id].events;
        uint32_t related_fd = prv_server_context.events[event_id].data.fd;

        if (event_handler & (EPOLLERR | EPOLLHUP | EPOLLRDHUP)) {
            continue;
        }
        
        if ((event_handler & EPOLLIN) && prv_server_context.fd == related_fd) {
            cnet_message_t msg;
            msg.address_len = sizeof(msg.recv_sock);

            msg.data_size = recvfrom(prv_server_context.fd, msg.data, sizeof(msg.data),
               0, &msg.recv_sock, &msg.address_len);

            msg.data[msg.data_size] = 0;

            getnameinfo(&msg.recv_sock, msg.address_len, msg.host, 
                sizeof(msg.host), msg.port, sizeof(msg.port), 
                NI_NUMERICHOST | NI_NUMERICSERV);
        
            recv_callback(&msg);
        }

    }

    return 0;
}

static int prv_init_udp_server(const char *uri, const char *port) {
    int ret = 0;
    struct addrinfo hints = {0};

    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_DGRAM; 
    hints.ai_flags = AI_PASSIVE; 

    struct addrinfo *res = NULL; 
    ret = getaddrinfo(uri, port, &hints, &res);
    if (ret != 0 ) { goto ret_err; }
    
    struct addrinfo *iter = NULL; 
    for (iter = res; iter != NULL; iter = iter->ai_next) {
        prv_server_context.fd = socket(iter->ai_family, iter->ai_socktype, iter->ai_protocol);
        if (prv_server_context.fd == -1) { continue; }

        if (bind(prv_server_context.fd, iter->ai_addr, iter->ai_addrlen) == 0) {
            if (prv_set_non_block() == -1) { continue; }
            break;
        }

        close(prv_server_context.fd);
    }

    prv_setup_epoll();

ret_err:
    if (res) freeaddrinfo(res);
    return ret;    
}


// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
// 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0 0 x 0 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0
// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0

int server_run(void) {
    int ret = prv_init_udp_server(SERVER_URI, SERVER_PORT);
    if (ret != 0) {
        LOG(ERROR, "Server cant be start");
        return -1;
    }
    LOG(INFO, "Server start %s:%s", SERVER_URI, SERVER_PORT);

    while (1) {
        prv_udp_step();
    }

    return 0;
}

#elif defined(_WIN32)
#   errors "The Windows port has not been crated yet"
#endif
