#include "syscall.h"
#include "htif.h"

void __attribute__ ((noreturn)) _exit(int code)
{
    uint64_t cmd = HTIF_TOHOST(0, 0, (code << 1) | 0x1);
    for (;;) {
        fromhost = 0;
        tohost = cmd;
    }
}
