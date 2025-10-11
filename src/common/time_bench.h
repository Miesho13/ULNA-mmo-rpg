#ifndef TIME_BENCH
#define TIME_BENCH

#include <stdint.h>
#include <stdbool.h>


#ifdef __linux__
#include <time.h>

typedef struct {
    struct timespec start;
    uint64_t duration_us;
} common_timert;

#endif

uint64_t time_now_us(void);

void     time_start(void);
uint64_t time_end_ns(void);

/* Example usage:
int main() {
    time_bench_t bench;
    time_start(&bench);

    // Code to benchmark
    for (volatile int i = 0; i < 1000000; i++);

    uint64_t ns = time_end(&bench);
    printf("Elapsed time: %lu ns (%.3f ms)\n", ns, ns/1e6);

    return 0;
}
*/

void time_reset(common_timert *tim, uint64_t val);
bool time_elapsed(common_timert *tim);


#endif //TIME_BENCH
