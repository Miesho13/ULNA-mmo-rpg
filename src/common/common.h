#ifndef ULNA_COMMON_H
#define ULNA_COMMON_H

#include <assert.h>
#include <stdio.h>
#include "common_cfg.h"

// Triggers an assertion failure with a message indicating that the function or 
// feature is not yet implemented. This is useful during development to catch 
// calls to incomplete functionalities and prevent further execution.
#define COMMON_NOT_IMPL_YET() assert(false && "Do not implemented yet")

// Retrieves the value at the specified (x, y) coordinates from a 1D buffer 
// representing a 2D array. The width parameter indicates the number of columns 
// in the 2D representation. The formula y*width + x calculates the correct 
// index in the 1D array.
#define GET_POSYTION_2D(buffer_1d, width, x, y) buffer_1d[y*width + x]

#define COMMON_LOG_INFO  "[INFO]" 
#define COMMON_LOG_ERROR "[ERROR]" 
#define LOG(LEVEL, msg, ...) printf(LEVEL" "msg"\n", ##__VA_ARGS__)
#ifdef LOG_DEBUG_LEVEL
#   define LOG_DEBUG(LEVEL, msg, ...) printf(LEVEL" "msg"\n", ##__VA_ARGS__)
#else
#   define LOG_DEBUG(...) 
#endif

typedef struct {
    float x;    
    float y;    
} v2_f32;

typedef struct {
    int x;    
    int y;    
} v2_i32;

#endif //ULNA_COMMON_H

