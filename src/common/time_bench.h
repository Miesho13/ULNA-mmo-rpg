#ifndef TIME_BENCH
#define TIME_BENCH

#include <stdint.h>

void time_start(void);
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

#endif //TIME_BENCH
