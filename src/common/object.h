#ifndef __OBJECT__
#define __OBJECT__

#include "./type.h"
#include "./dynamic_array.h"
#include "./event.h"

typedef enum {
    PLAYER = 0x0,
    GRAUND, 

    OBJECT_TYPE_COUNT
} object_type_t;

typedef struct {
    uint32_t id;
    object_type_t object_type;
    event_t event[EVENT_COUNT];
} interface_object;
#define _INTEFACE_OBJECT_SIZE (sizeof(interface_object))

#endif
