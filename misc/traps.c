#include <stdint.h>
#include "syscall.h"

void __attribute__((weak)) handle_trap(uintptr_t epc, uintptr_t cause, uintptr_t tval, uintptr_t regs[32])
{
    int code = (((intptr_t)cause < 0) << 8) | ((cause & 0xf) << 4) | 0x1;
    _exit(code);
}
