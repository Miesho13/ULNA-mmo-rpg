/*
------------------------------------------------------------------------------
dynamic_array.h - generic dynamic array (stb-style, macro-based)

Usage:
    #define DYNARR_IMPLEMENTATION
    #include "dynamic_array.h"

Example:
    dynarr(int) a = {0};
    dynarr_push(a, 123);
    dynarr_push(a, 456);

    for (size_t i = 0; i < dynarr_len(a); ++i)
        printf("%d\n", a[i]);

    dynarr_free(a);

Notes:
    - This stores a small header right before the data pointer:
      [cap][len] then element data.
    - Similar idea to stb_ds.
------------------------------------------------------------------------------
*/

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stddef.h> 
#include <string.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DYNARR_ASSERT
#   include <assert.h>
#   define DYNARR_ASSERT(x) assert(x)
#endif

static inline void *dynarr__realloc(void *p, size_t bytes);
static inline void *dynarr__reserve(void *a, size_t new_cap, size_t elem_size);
static inline void *dynarr__grow(void *a, size_t add_n, size_t elem_size);

#define dynarr(T) T*

#define dynarr__hdr(a) ((size_t*)( (char*)(a) - 2*sizeof(size_t) ))
#define dynarr__cap(a) ( (a) ? dynarr__hdr(a)[0] : 0u )
#define dynarr__len(a) ( (a) ? dynarr__hdr(a)[1] : 0u )

#define dynarr_len(a) dynarr__len(a)
#define dynarr_cap(a) dynarr__cap(a)

#define dynarr_free(a) do {                      \
    if (a) free(dynarr__hdr(a));                 \
    (a) = NULL;                                  \
} while (0)

#define dynarr_clear(a) do {                     \
    if (a) dynarr__hdr(a)[1] = 0u;               \
} while (0)

#define dynarr_push(a, v) do {                   \
    (a) = dynarr__grow((a), 1, sizeof(*(a)));    \
    (a)[dynarr__hdr(a)[1]++] = (v);              \
} while (0)

#define dynarr_pop(a) (                          \
    DYNARR_ASSERT(dynarr_len(a) > 0),            \
    (a)[--dynarr__hdr(a)[1]]                     \
)

#define dynarr_reserve(a, n) do {                \
    size_t __need = (n);                         \
    if (dynarr_cap(a) < __need)                  \
        (a) = dynarr__reserve((a), __need, sizeof(*(a))); \
} while (0)

#define dynarr_resize(a, n) do {                 \
    size_t __n = (n);                            \
    if (!(a) || dynarr_cap(a) < __n)             \
        (a) = dynarr__reserve((a), __n, sizeof(*(a))); \
    dynarr__hdr(a)[1] = __n;                     \
} while (0)

#define dynarr_pushn(a, ptr, n) do {                         \
    size_t __n = (n);                                        \
    (a) = dynarr__grow((a), __n, sizeof(*(a)));              \
    memcpy((a) + dynarr__hdr(a)[1], (ptr), __n*sizeof(*(a)));\
    dynarr__hdr(a)[1] += __n;                                \
} while (0)

#ifdef DARRAY_IMPLEMENTATION

static inline void *dynarr__realloc(void *p, size_t bytes) {
    return realloc(p, bytes);
}

static inline void *dynarr__reserve(void *a, size_t new_cap, size_t elem_size) {
    size_t len = dynarr__len(a);
    if (new_cap < len) new_cap = len;

    size_t header_bytes = 2*sizeof(size_t);
    size_t data_bytes   = new_cap * elem_size;

    size_t *base = (size_t*)dynarr__realloc(a ? (void*)dynarr__hdr(a) : NULL,
                                           header_bytes + data_bytes);
    if (!base) return NULL;

    if (!a) base[1] = 0;
    base[0] = new_cap;

    return (char*)base + header_bytes;
}

static inline void *dynarr__grow(void *a, size_t add_n, size_t elem_size) {
    size_t len = dynarr__len(a);
    size_t cap = dynarr__cap(a);
    size_t need = len + add_n;

    if (need <= cap) return a;

    size_t new_cap = cap ? cap : 8u;
    while (new_cap < need) new_cap *= 2u;

    return dynarr__reserve(a, new_cap, elem_size);
}

#endif // DARRAY_IMPLEMENTATION

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* DYNAMIC_ARRAY_H */
