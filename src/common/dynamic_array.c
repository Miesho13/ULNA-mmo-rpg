#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "dynamic_array.h"

#define _vec_get_size(vec)          ((_vec_header*)vec)[-1].size
#define _vec_get_capasity(vec)      ((_vec_header*)vec)[-1].capasity
#define _vec_get_element_size(vec)  ((_vec_header*)vec)[-1].element_size

typedef struct {
    uint32_t element_size;
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
    header->element_size = element_size;
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

void vec_push(vec_array vec, void *val) {
    assert(vec && "NULL reference in vector");
    if (_vec_get_capasity(vec) < _vec_get_size(vec)) {
        // !TODO(marcin.ryzewskii@gmail.com): Implementation of memory resize.
        return;
    }
    uint8_t *head = vec;
    head += (_vec_get_size(vec)*_vec_get_element_size(vec));
    memcpy(head, val, _vec_get_element_size(vec));
    _vec_get_size(vec)++;
}

void* vec_get(vec_array vec, uint32_t index) {
    assert(vec && "NULL reference in vector");
    assert(_vec_get_capasity(vec) > index && "The index is out of range.");
    assert(_vec_get_size(vec) > index && "The element dosen't exist.");
    uint8_t *head = vec;
    head += (index*_vec_get_element_size(vec));
    return (void*)head;
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
    assert(capasity > index && "The index aout of range.");
    assert(size > index && "Element dosen't exist.");
    return ((int*)vec)[index];
}
