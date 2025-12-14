#include "hit_grid.h"

#include <stdint.h>
#include <stdio.h>


static inline uint32_t hash(int x, int y)
{
    return (x << 7) | y; 
}

void hit_grid_init(hit_grid *ctx, int height, int width) 
{
    ctx->cell_size.width = width;
    ctx->cell_size.height = height;
}

int hit_grid_push(hit_grid *ctx, int x, int y, hit_event event) 
{
    const uint32_t hash_value = hash(x, y);
    if (hash_value >= BUCKET_SIZE) {
        return 1;
    }
    ctx->bucket[hash_value] = event;
    return 0;
}

hit_event* hit_grid_get(hit_grid *ctx, int x, int y) 
{
    const uint32_t hash_value = hash(x, y);
    if (hash_value >= BUCKET_SIZE) {
        return NULL;
    }

    return &ctx->bucket[hash_value]; 
}

grid_pos hit_grid_pixel_to_cell(hit_grid *ctx, int x, int y) 
{
    return (grid_pos){ x/ctx->cell_size.width, y/ctx->cell_size.height};
}
