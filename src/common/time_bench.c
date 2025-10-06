#include "time_bench.h"

#include <assert.h>

#ifdef __linux__
#include <time.h>

struct {
    struct timespec start;
    struct timespec end;
    uint64_t elapsed; 

} TIM;

void time_start(void) {
    clock_gettime(CLOCK_MONOTONIC, &TIM.start);
}

uint64_t time_end_ns(void) {
    clock_gettime(CLOCK_MONOTONIC, &TIM.end);

    uint64_t start_ns = (uint64_t)TIM.start.tv_sec * 1000000000ULL + TIM.start.tv_nsec;
    uint64_t end_ns   = (uint64_t)TIM.end.tv_sec * 1000000000ULL + TIM.end.tv_nsec;

    TIM.elapsed = end_ns - start_ns;
    return TIM.elapsed;
}

uint64_t time_now_us(void);
uint64_t time_now_us(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000ULL + ts.tv_nsec / 1000ULL;
}

void time_reset(common_timert *tim, uint64_t val_us) {
    tim->duration_us = val_us;
    clock_gettime(CLOCK_MONOTONIC, &tim->start);
}

bool time_elapsed(common_timert *tim) {
    uint64_t start_us = (uint64_t)tim->start.tv_sec * 1000000ULL +
                        tim->start.tv_nsec / 1000ULL;

    uint64_t now = time_now_us();
    return (now - start_us) >= tim->duration_us;
}

#else

void time_start(void) {
    assert(0 && "DO NOT IMPL");
}

uint64_t time_end_ns(void) {
    assert(0 && "DO NOT IMPL");
    return 0;
}


#endif
