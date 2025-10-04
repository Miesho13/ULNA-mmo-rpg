#ifndef ULNA_COMMON_H
#define ULNA_COMMON_H

#include <assert.h>
#include <stdio.h>

#define COMMON_NOT_IMPL_YET() assert(false && "Do not implemented yet")


// ---------- LOGS ----------------
#define LOG_INFO  "[INFO]" 
#define LOG_ERROR "[ERROR]" 

#define LOG(LEVEL, msg, ...) printf(LEVEL" "msg"\n", ##__VA_ARGS__)

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

