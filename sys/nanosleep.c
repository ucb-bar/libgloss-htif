#include <errno.h>
#include <sys/time.h>
#include "syscall.h"

int nanosleep(const struct timespec *rqtp, struct timespec *rmtp)
{
    errno = ENOSYS;
    return -1;
}
