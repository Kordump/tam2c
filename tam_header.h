#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

static int fd_segv[2];

void init_segv();
void close_segv();
bool check_segv(void* addr);

struct tam_reg
{
    size_t* CB; // code base (constant)
    size_t* CT; // code top (constant)
    size_t* PB; // primitive base (constant)
    size_t* PT; // primitive top (constant)
    size_t* SB; // stack base (constant)
    size_t* ST; // stack top
    size_t* HB; // heap base (constant)
    size_t* HT; // heap top
    size_t* LB; // local base (call+return)
    size_t* L1; // local base 1
    size_t* L2; // local base 2
    size_t* L3; // local base 3
    size_t* L4; // local base 4
    size_t* L5; // local base 5
    size_t* L6; // local base 6
    size_t* CP; // code pointer
};

int tam_body(void* stack_base);
