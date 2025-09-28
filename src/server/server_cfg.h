#ifndef SERVER_CFG
#define SERVER_CFG

#include <stdint.h>

#define CNET_TX_BUFFER_MAX_SIZE (4*1024)
#define CNET_EPOLL_MAX_EVENT (10)
#define EVENT_POLL_SIZE (64)

#define SERVER_URI  "127.0.0.1"
#define SERVER_PORT "6969"

#define MAX_PLAYER_COUNT (UINT16_MAX)

#endif // SERVER_CFG 

