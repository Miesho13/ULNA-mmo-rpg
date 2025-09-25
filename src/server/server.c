#include "server.h"
#include "common.h"

#include "server_cfg.h"

#ifdef __linux__

#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/epoll.h>

#define CNET_EPOLL_MAX_EVENT (10)
#define EVENT_POLL_SIZE (64)

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

int server_run(void) {
    // int ret = prv_init_udp_server(SERVER, PORT);
    LOG(INFO, "Server start %s:%s", SERVER_URI, SERVER_PORT);
    return 0;
}

#elif defined(_WIN32)
#   errors "The Windows port has not been crated yet"
#endif
