#include <stdlib.h>

#include "server.h"
#include "common.h"
#include "server_client_io.h"
#include "server_cfg.h"

#include <string.h>
#include <stdbool.h>

#ifdef __linux__

#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/epoll.h>

static struct {
    int fd; 
    int epollfd;
    struct epoll_event ev;
    struct epoll_event events[EVENT_POLL_SIZE];
    bool is_server_run;
    recv_callback recv;
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
        
            if (prv_server_context.recv) {
                prv_server_context.recv(&msg);
            }
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

int server_send(const void *buffer, size_t buffer_len, 
                struct sockaddr *recv_sock,
                socklen_t address_len) {

    return sendto(prv_server_context.fd, buffer, 
            buffer_len, 0, recv_sock, address_len);
}

int server_init(recv_callback recv) {
    prv_server_context.recv = recv;

    int ret = prv_init_udp_server(SERVER_URI, SERVER_PORT);
    if (ret != 0) {
        LOG(LOG_ERROR, "Server cant be start");
        return SERVER_ERR;
    }
    LOG(LOG_INFO, "Server start %s:%s", SERVER_URI, SERVER_PORT);

    prv_server_context.is_server_run = true;
    return SERVER_OK;
}

int server_step(void) {
    prv_udp_step();
    return SERVER_OK;
}

#elif defined(_WIN32)
#   errors "The Windows port has not been crated yet"
#endif
