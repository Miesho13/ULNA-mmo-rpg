#ifndef FIX_STACK
#define FIX_STACK

#include <stdlib.h>
#include <stdint.h>

typedef struct {
    void* head;
    size_t element_cont;
    size_t max;
} fix_stack;

void fix_stack_init(fix_stack *self, void *buffer, size_t len);
size_t fix_stack_count(fix_stack *self);

void fix_stack_push_int32(fix_stack *self, int32_t val);
int  fix_stack_get_int32(fix_stack *self);

void fix_stack_pop_int32(fix_stack *self);
void fix_stack_pop_int32(fix_stack *self);

#endif // FIX_STACK
