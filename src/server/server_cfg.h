#ifndef SERVER_CFG
#define SERVER_CFG

#include <stdint.h>

#define CNET_TX_BUFFER_MAX_SIZE (4*1024)
#define CNET_EPOLL_MAX_EVENT (10)
#define EVENT_POLL_SIZE (64)

#define SERVER_URI  "127.0.0.1"
#define SERVER_PORT "6969"

#define MAX_PLAYER_COUNT (UINT16_MAX)

#define WIN 11 
#define WORD_MAP (255 * 255)
#define WORD_MAP_H (255)
#define WORD_MAP_W (255)

// TIMERS REST VALUES 
#define SERVER_COLLECTION_DATA_US (30 * 1000) 

#endif // SERVER_CFG 

