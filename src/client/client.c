#include "client.h"
#include "../common/common.h"

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

int client_send(uint8_t *msg, size_t len) {
    return (int)send(prv_client_context.fd, msg, len, 0);
}

#elif defined(_WIN32)
#   errors "The Windows port has not been crated yet"
#endif
