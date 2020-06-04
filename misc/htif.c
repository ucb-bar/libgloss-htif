#include <stdint.h>

#include "atomic.h"
#include "spinlock.h"
#include "htif.h"

volatile uint64_t tohost __attribute__ ((section (".htif")));
volatile uint64_t fromhost __attribute__ ((section (".htif")));

static spinlock_t htif_lock = SPINLOCK_INIT;

long htif_syscall(uint64_t a0, uint64_t a1, uint64_t a2, unsigned long n)
{
    volatile uint64_t buf[8];
    uint64_t sc;

    buf[0] = n;
    buf[1] = a0;
    buf[2] = a1;
    buf[3] = a2;

    sc = HTIF_TOHOST(0, 0, (uintptr_t)&buf);
    spin_lock(&htif_lock);
    wmb();
    tohost = sc;
    while (fromhost == 0);
    fromhost = 0;
    spin_unlock(&htif_lock);

    rmb();
    return buf[0];
}
