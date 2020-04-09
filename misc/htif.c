#include <stdint.h>

#include "spinlock.h"
#include "htif.h"

volatile uint64_t tohost __attribute__ ((section (".htif")));
volatile uint64_t fromhost __attribute__ ((section (".htif")));

static spinlock_t htif_lock = SPINLOCK_INIT;

void htif_syscall(uintptr_t arg)
{
    arg = HTIF_TOHOST(0, 0, arg);
    spin_lock(&htif_lock);
    tohost = arg;
    while (fromhost == 0);
    fromhost = 0;
    spin_unlock(&htif_lock);
}
