#ifndef __OBJECT__
#define __OBJECT__

#include "./type.h"
#include "./dynamic_array.h"
#include "./event.h"

typedef enum {
    LAYER = 0x0,
    NPC,
    MOB,

    OBJECT_TYPE_COUNT
} object_type_t;

typedef struct {
    object_type_t object_type;
    vector2_int_t game_pos;

} interface_object;
#define _INTEFACE_OBJECT_SIZE (sizeof(interface_object))

#endif
