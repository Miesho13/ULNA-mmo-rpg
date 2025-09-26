#ifndef SERVER_CLIENT_IO
#define SERVER_CLIENT_IO

#include <stdint.h>

typedef enum  {
    HELLO = 0x11,
    MOVE = 0x1,
    IDLE = 0x11,

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
    uint32_t id;
} register_respone_t;

typedef struct {
    uint8_t head; 
    uint32_t id;
} good_bye_request_t;

typedef struct {
    uint8_t head; 
    uint32_t id;
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

// HELPER FUNCTION

 
#endif // SERVER_CLIENT_IO

