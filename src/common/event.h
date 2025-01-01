/*
 * This file contains the event system for the game. It is implemented as a 
 * common module because events will be used by both the client and the server.
 *
 */

#ifndef __EVENT__
#define __EVENT__

#include <stdint.h>
typedef enum {
    EMPTY = 0,
    
    EVENT_COUNT
} EVENT_ID;

typedef void (*event_call)(void*);
typedef struct {
    uint32_t id;
    event_call call;
} event;

#endif
