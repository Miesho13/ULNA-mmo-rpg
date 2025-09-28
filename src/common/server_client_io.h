#ifndef SERVER_CLIENT_IO
#define SERVER_CLIENT_IO

#include <stdint.h>

typedef enum  {
    HELLO = 0x11,
    MOVE = 0x1,
    IDLE = 0x11,
    UPDATE = 0x69,

    GOOD_BYE = 0xfd,
    NONE = 0xff,
} head_t;

typedef enum  {
    HELLO_OK = 0x11,
    EVENT_OK = 0x42,
} rec_head_t;

typedef struct {
    uint8_t head; 
} register_request_t;

typedef struct {
    uint8_t head; 
    uint16_t id;
} register_respone_t;

typedef struct {
    uint8_t head; 
    uint16_t id;
} good_bye_request_t;

typedef struct {
    uint8_t head; 
    uint16_t id;
    struct {
        int dx; 
        int dy; 
    } dpos;
} event_request_t;

typedef struct {
    uint8_t head; 
    struct {
        int x; 
        int y; 
    } pos;
    uint8_t players[11*11];
} event_respone_t;

#define PLAYER_MAP_SIZE 11*11
#define EVENT_MAX_SIZE  64

typedef struct {
    uint16_t who_id;
    uint16_t to_whom;
    uint8_t action;
} event;

typedef struct {
    uint8_t head; 
    struct {
        int x; 
        int y; 
    } pos;
    uint16_t player_map[PLAYER_MAP_SIZE]; 
    uint8_t npc_map[PLAYER_MAP_SIZE]; 
    event   action[EVENT_MAX_SIZE]; 
} update_respone;

// HELPER FUNCTION

 
#endif // SERVER_CLIENT_IO

