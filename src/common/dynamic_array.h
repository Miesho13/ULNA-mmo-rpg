#ifndef __DYNAMIC_ARRAY__
#define __DYNAMIC_ARRAY__

#include <stdint.h>

typedef void* vec_array;
typedef void* vec_int_c;

// General operation
vec_array vec_array_new(uint32_t capasity, uint32_t element_size);
uint32_t vec_size(vec_array vec);
uint32_t vec_capasity(vec_array vec);
void vec_push(vec_array vec, void *val);
void vec_pop(vec_array vec);
void* vec_get(vec_array vec, uint32_t index);

// int operation 
void vec_push_back_int(vec_array vec, int val);
int vec_get_int(vec_array vec, uint32_t index);
void vec_pop_int(vec_array vec);

#endif
