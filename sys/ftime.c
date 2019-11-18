#include <errno.h>
#include <sys/timeb.h>
#include "syscall.h"

int _ftime(struct timeb *tp)
{
    errno = ENOSYS;
    return -1;
}
