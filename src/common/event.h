/*
 * This file contains the event system for the game. It is implemented as a 
 * common module because events will be used by both the client and the server.
 *
 */

#ifndef __EVENT__
#define __EVENT__

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    HELLO = 0,

    EVENT_COUNT
} EVENT_ID;

typedef void (*event_call)(void*);
typedef struct {
    bool is_define;
    event_call call;
} event_t;

#endif
