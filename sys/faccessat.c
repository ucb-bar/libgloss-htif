#include <errno.h>
#include "syscall.h"

int _faccessat(int dirfd, const char *file, int mode, int flags)
{
    errno = EBADF;
    return -1;
}
