#ifndef SERVER_CFG
#define SERVER_CFG

#include <stdint.h>

#define SERVER_URI  "127.0.0.1"
#define SERVER_PORT "6969"

#define CNET_TX_BUFFER_MAX_SIZE (4*1024)
#define CNET_EPOLL_MAX_EVENT (10)
#define EVENT_POLL_SIZE (64)

#define MAX_PLAYER_COUNT (UINT16_MAX)


// TIMERS REST VALUES 
#define SERVER_COLLECTION_DATA_US (10 * 1000) 

// Parameters for a linear buffer representing the local 
// player's game state
#define WORLD_LOCAL_W (11)
#define WORLD_LOCAL_H (11)
#define WORLD_LOCAL_BUFFER (WORLD_LOCAL_W * WORLD_LOCAL_H)

// Parameters for a linear buffer representing the entire 
// world map
#define WORLD_MAP_H (255)
#define WORLD_MAP_W (255)
#define WORLD_MAP (WORLD_MAP_W * WORLD_MAP_H)

#endif // SERVER_CFG 

