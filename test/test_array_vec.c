#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "../src/common/dynamic_array.h"

int main(void) {
    vec_array vec = vec_array_new(1024, sizeof(int));
    if (vec_capasity(vec) != 1024) {
        fprintf(stderr, "The vector capacity value is not correct. Expected 1024: (%d)", vec_capasity(vec));
        return 1;
    }

    for (uint32_t i = 0; i < vec_capasity(vec); i++) {
        vec_push_back_int(vec, i);
    }
    if (vec_size(vec) != 1024) {
        fprintf(stderr, "The vector size value is not correct. Expected 1024: (%d)", vec_size(vec));
        return 2;
    }
    
    for (uint32_t i = 0; i < vec_capasity(vec); i++) {
        vec_pop_int(vec);
    }
    if (vec_size(vec) != 0) {
        fprintf(stderr, "The vector size value is not correct. Expected 0: (%d)", vec_size(vec));
        return 3;
    }

    return 0;
}
