#ifndef SERVER_H 
#define SERVER_H 

#include "server_cfg.h"

#ifdef __linux__
#   include <fcntl.h>
#   include <arpa/inet.h>
#   include <sys/socket.h>
#   include <sys/types.h>
#   include <unistd.h>
#   include <netinet/in.h>
#   include <netdb.h>
#   include <sys/epoll.h>
#endif

#define SERVER_OK  ( 0)
#define SERVER_ERR (-1)

typedef struct  {
    uint8_t data[CNET_TX_BUFFER_MAX_SIZE];
    uint32_t data_size;
    char host[NI_MAXHOST];
    char port[NI_MAXSERV];
    struct sockaddr recv_sock;
    socklen_t address_len; 
} cnet_message_t;

typedef void (*recv_callback)(cnet_message_t* msg);

int server_init(recv_callback recv);
int server_step(void);
int server_send(const void *buffer, size_t buffer_len, 
                struct sockaddr *recv_sock,
                socklen_t address_len);

#endif // SERVER_H
