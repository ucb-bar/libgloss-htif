#include <errno.h>
#include "syscall.h"

int _openat(int dirfd, const char *name, int flags, int mode)
{
    errno = ENOENT;
    return -1;
}
