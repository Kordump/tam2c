#include "tam_header.h"

#define TAM_NO_REVERSE_STACK

#ifdef TAM_NO_REVERSE_STACK
    #ifndef TAM_STACK_SIZE
        #define TAM_STACK_SIZE -1
    #endif

int main(int argc, char* argv[])
{
    size_t page_size;
    if(TAM_STACK_SIZE < 0)
        page_size = sysconf(_SC_PAGESIZE);
    else
        page_size = TAM_STACK_SIZE;

    size_t stack_base[page_size];
    return tam_body(stack_base);
}

#else

void init_segv()
{
    if(pipe(fd_segv) < 0)
        exit(-1);
}

void close_segv()
{
    close(fd_segv[0]);
    close(fd_segv[1]);
}

bool check_segv(void* addr)
{
    return (write(fd_segv[1], addr, sizeof(size_t)) > 0);
}

int main(int argc, char* argv[])
{
    init_segv();
    size_t page_size = sysconf(_SC_PAGESIZE);

    size_t stack_size = 0;
    size_t* frame_base = &page_size + 1;
    for(size_t step = page_size; step > 0; --step)
    {
        if(check_segv(frame_base - stack_size))
        {
            stack_size += step;
            ++step;
        } else {
            if(step > stack_size)
                stack_size -= stack_size;
            else
                stack_size -= step;
            step /= 2;
        }
    }

    for(size_t i = 0; i < page_size; ++i)
        assert(check_segv(frame_base - stack_size + i));

    close_segv();
    return tam_body(frame_base - stack_size + 1);
}

#endif


