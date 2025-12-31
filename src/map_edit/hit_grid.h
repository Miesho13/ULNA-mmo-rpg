#ifndef __EVENT__
#define __EVENT__

#include <stdlib.h>

#define BUCKET_SIZE (1 << 15)

typedef struct _hit_event hit_event;
typedef void (*input_callback)(hit_event *context);

typedef struct _hit_event {
    union {
        unsigned int u32;
        int i32;

        short i16;
        unsigned short u16;

        char i8;
        unsigned char u8;
    } value;

    void *user_arg;
    input_callback call;
} hit_event;

typedef struct {
    hit_event bucket[BUCKET_SIZE];
    struct {
        int width;
        int height;
    } cell_size;

} hit_grid;

typedef struct {
    int x;
    int y;
} hit_grid_pos;

void           hit_grid_init(hit_grid *ctx, int hight, int width);
int            hit_grid_push(hit_grid *ctx, int x, int y, hit_event event);
hit_event*     hit_grid_get(hit_grid *ctx, int x, int y);
hit_grid_pos   hit_grid_pixel_to_cell(hit_grid *ctx, int x, int y);

#endif // __EVENT__
