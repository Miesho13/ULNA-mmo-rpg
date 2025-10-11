#ifndef ULNA_COMMON_H
#define ULNA_COMMON_H

#include <assert.h>
#include <stdio.h>
#include "common_cfg.h"

#define COMMON_NOT_IMPL_YET() assert(false && "Do not implemented yet")

// ---------- LOGS ----------------
#define COMMON_LOG_INFO  "[INFO]" 
#define COMMON_LOG_ERROR "[ERROR]" 

#define LOG(LEVEL, msg, ...) printf(LEVEL" "msg"\n", ##__VA_ARGS__)

#ifdef LOG_DEBUG_LEVEL
#   define LOG_DEBUG(LEVEL, msg, ...) printf(LEVEL" "msg"\n", ##__VA_ARGS__)
#else
#   define LOG_DEBUG(...) 
#endif

// ---------- END LOGS ----------------

// ----------- vectore ----------------
typedef struct {
    float x;    
    float y;    
} v2_f32;

typedef struct {
    int x;    
    int y;    
} v2_i32;

#endif //ULNA_COMMON_H

