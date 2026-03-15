#ifndef __TYPE__
#define __TYPE__

#include <stdint.h>

typedef uint8_t   u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t   i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float  f32;
typedef double f64;

typedef struct {
    u8 x;
    u8 y;
} vector2_u8;

typedef struct {
    u16 x;
    u16 y;
} vector2_u16;

typedef struct {
    u32 x;
    u32 y;
} vector2_u32;

typedef struct {
    u64 x;
    u64 y;
} vector2_u64;

typedef struct {
    f32 x;
    f32 y;
} vector2_f32;

typedef struct {
    f64 x;
    f64 y;
} vector2_f64;

#endif // __TYPE__
