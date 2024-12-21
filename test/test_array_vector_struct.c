#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "dynamic_array.h"
#include  "renderer.h"

int main(void) {
    vec_array objs = vec_array_new(1024, sizeof(render_obj));
    if (vec_capasity(objs) != 1024 || vec_size(objs) != 0) {
        return 1;
    }
    
    vec_push(objs, &((render_obj){(Vector2){1.f, 2.f}, 15}));
    render_obj *obj = vec_get(objs, 0);
    printf("[INFO] id: %d vec2: {%f %f}", obj->id, obj->pos.x, obj->pos.y);
    assert(obj->id == 15 && "Obj->id incorrect value. Expected 15");
    assert(obj->pos.x == 1.f && obj->pos.y == 2.f && "Obj->pos incorrect value. Expected {1.f 2.f}");

    return 0;
}
