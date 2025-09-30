#include "client.h"
#include "../common/common.h"
#include "server_client_io.h"
#include <string.h>

#include <stdio.h>

#define _SERVER "localhost" 
#define _PORT "6969" 

#ifdef __linux__
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/epoll.h>

static client_context prv_client_context;
client_context* get_client(void) {
    return &prv_client_context;
}

int hello_to_server(void) {
    client_init();

    register_request_t hello_msg = {
        .head = HELLO,
    };

    client_send((uint8_t*)&hello_msg, sizeof(hello_msg));

    register_respone_t register_respone = {0};
    client_recv((uint8_t*)&register_respone, sizeof(register_respone));

    if (register_respone.head != HELLO_OK) {
        return -1;
    }

    return register_respone.id;
}

void good_bye(uint16_t id) {
    good_bye_request_t request = {
        .head = GOOD_BYE,
        .id = id,
    };
    client_send((uint8_t *)&request, sizeof(request));
}

void send_chang_pos(int id, int dx, int dy, uint16_t players[PLAYER_MAP_SIZE]) {
    event_request_t request = {
        .head = MOVE, 
        .id = id, 
        .dpos = {
            .dx = dx, 
            .dy = dy
        }
    };

    client_send((uint8_t *)&request, sizeof(request));

    update_respone_t respone = {0};
    client_recv((uint8_t*)&respone, sizeof(respone));

    // TODO(marcin.ryzewski): we can remove this extra copy. Symple just have
    // static buffer for recv update client
    memcpy(players, respone.player_map, sizeof(uint16_t)*PLAYER_MAP_SIZE);
}

int client_push_event(event_request_t *event_request) {
    if (prv_client_context.fd > 0) {
        return client_send((uint8_t*)event_request, sizeof(event_request_t));
    }
    return -1;
}

int client_recv_update_event(update_respone_t *update_respone) {
    if (prv_client_context.fd > 0) {
        return client_recv((uint8_t*)update_respone, sizeof(*update_respone));
    }
    return -1;
}


static void prv_client_hendhake(void) {

}

int client_init(void) {
    int ret = -1;
    struct addrinfo hints = {0};

    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_DGRAM; 
    hints.ai_flags    = AI_PASSIVE; 

    struct addrinfo *res = NULL; 
    ret = getaddrinfo(_SERVER, _PORT, &hints, &res);
    if (ret != 0 ) { goto ret_err; }

    struct addrinfo *iter = NULL; 
    for (iter = res; iter != NULL; iter = iter->ai_next) {
        prv_client_context.fd = socket(iter->ai_family, iter->ai_socktype, iter->ai_protocol);              
        if (prv_client_context.fd == -1) { 
            continue; 
        }

        if (connect(prv_client_context.fd, iter->ai_addr, iter->ai_addrlen) == -1) {
            fprintf(stderr, "Cant establish connect\n");
            goto ret_err;
        }
    }

    freeaddrinfo(res);
    return 0;

ret_err:
    if (res) freeaddrinfo(res);
    if (prv_client_context.fd > 0) {
        close(prv_client_context.fd != 0);
        prv_client_context.fd = -1;
    }
    return -1;    
}

int clinet_service() {

}

int client_send(uint8_t *msg, size_t len) {
    return (int)send(prv_client_context.fd, msg, len, 0);
}

int client_recv(uint8_t *msg, size_t len) {
    return (int)recv(prv_client_context.fd, msg, len, 0);
}

#elif defined(_WIN32)
#   errors "The Windows port has not been crated yet"
#endif
