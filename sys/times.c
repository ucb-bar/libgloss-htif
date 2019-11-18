#include <errno.h>
#include <sys/times.h>
#include "syscall.h"

clock_t _times(struct tms *buf)
{
    errno = ENOSYS;
    return -1;
}
