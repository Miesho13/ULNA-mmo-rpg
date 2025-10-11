#ifndef WORLD_CFG
#define WORLD_CFG

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

#endif
