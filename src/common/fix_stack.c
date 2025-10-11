#include "fix_stack.h"

void fix_stack_init(fix_stack *self, void *buffer, size_t len) {
    if (!buffer) {
        return;
    }

    self->head = buffer;
    self->max = len;
    self->element_cont = 0;
}

size_t fix_stack_count(fix_stack *self) {
    return self->element_cont;
}

void fix_stack_push_int32(fix_stack *self, int32_t val) {
    if ((self->element_cont) >= self->max) {
        return;
    }

    if (!self->head) {
        return;
    }

    *(int*)self->head = val;

    self->head = (int*)self->head + 1;
    self->element_cont++;
}

int fix_stack_get_int32(fix_stack *self) {
    return *((int*)self->head - 1);
}

void fix_stack_pop_int32(fix_stack *self) {
    if (self->element_cont == 0) {
        return;
    }

    self->head = (int*)self->head - 1;
    self->element_cont--;
}
