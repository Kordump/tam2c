#include "tam_header.c"

int tam_body(void* stack_base)
{
    printf("lol : %lu", size_t(stack_base));
    for(size_t i = 0; i < 2 << 18; ++i)
        ((int*) stack_base)[i] = 1;
    return 0;
}

