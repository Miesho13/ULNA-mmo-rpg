#ifndef __CANVAS__
#define __CANVAS__

#include <stdint.h>
#include "raylib.h"

typedef struct {
    void *data;
    uint32_t sizie;

} canvas_drawable_descriptor_t;

typedef struct {
    Camera2D camera;
    
    
} canvas_ctx_t;


void canvas_init(uint32_t posx, uint32_t posy, uint32_t with, uint32_t hight);
void canvas_update(canvas_ctx_t ctx, canvas_drawable_descriptor_t *draw);

#endif
