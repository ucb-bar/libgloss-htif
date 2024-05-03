#include <stddef.h>
#include <errno.h>
#include "syscall.h"
#include "compiler.h"

extern char __end[];
static char *curbrk = __end;

void *_sbrk(ptrdiff_t incr) {
    extern char __heap_end[];
    char *newbrk;
    char *oldbrk;

    oldbrk = curbrk;
    newbrk = oldbrk + incr;
    if (unlikely((newbrk < __end) || (newbrk >= __heap_end))) {
        errno = ENOMEM;
        return (void *)(-1);
    }

    curbrk = newbrk;
    return oldbrk;
}
