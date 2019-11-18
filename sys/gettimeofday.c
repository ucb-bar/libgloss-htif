#include <errno.h>
#include <sys/time.h>
#include "syscall.h"

int _gettimeofday(struct timeval *tp, void *tzp)
{
    errno = ENOSYS;
    return -1;
}
