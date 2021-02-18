#include <errno.h>
#include <sys/time.h>
#include "syscall.h"
#include "encoding.h"

#ifndef CLOCK_FREQ
#define CLOCK_FREQ (500000000UL)
#endif

int _gettimeofday(struct timeval *tp, void *tzp)
{
    uint64_t t = rdcycle();
    tp->tv_sec = t / CLOCK_FREQ;
    tp->tv_usec = (t % CLOCK_FREQ) / (CLOCK_FREQ / 1000000U);
    return 0;
}
