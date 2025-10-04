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

#else
void time_start(void) {
    assert(0 && "DO NOT IMPL");
}

uint64_t time_end_ns(void) {
    assert(0 && "DO NOT IMPL");
    return 0;
}

#endif
