#include <stdlib.h>
#include <assert.h>
#include "dynamic_array.h"

#define _vec_get_size(vec) ((_vec_header*)vec)[-1].size
#define _vec_get_capasity(vec) ((_vec_header*)vec)[-1].capasity

typedef struct {
    uint32_t size; 
    uint32_t capasity;
    uint8_t data[];
} _vec_header;

static inline _vec_header* _vec_new(uint32_t capasity) {
    _vec_header *header = calloc(sizeof(uint8_t), sizeof(*header) + capasity);
    return header;
}

vec_array vec_array_new(uint32_t capasity, uint32_t element_size) {
    _vec_header *header = _vec_new(capasity*element_size);
    header->capasity = capasity;
    return (void*)header->data;
}

uint32_t vec_size(const vec_array vec) {
    if (!vec) return 0;
    const _vec_header *header = vec;
    return header[-1].size;
}

uint32_t vec_capasity(const vec_array vec) {
    if (!vec) return 0;
    const _vec_header *header = vec;
    return header[-1].capasity;
}

void vec_push_back_int(vec_array vec, int val) {
    assert(vec && "NULL reference in vector");
    uint32_t size = _vec_get_size(vec);
    uint32_t capasity = _vec_get_capasity(vec);
    if (capasity < size) {
        // !TODO(marcin.ryzewskii@gmail.com): Implementation of memory resize.
        return;
    }
    ((int*)vec)[size] = val;
    _vec_get_size(vec)++;
}

void vec_pop_int(vec_array vec) {
    assert(vec && "NULL reference in vector");
    assert(_vec_get_size(vec) > 0 && "Index aout of range.");
    _vec_get_size(vec)--;
}

int vec_get_int(const vec_array vec, uint32_t index) {
    assert(vec && "NULL reference in vector.");
    uint32_t size = _vec_get_size(vec);
    uint32_t capasity = _vec_get_capasity(vec);
    assert(capasity > index && "Index aout of range.");
    assert(size > index && "Element dosen't exist.");
    return ((int*)vec)[index];
}
