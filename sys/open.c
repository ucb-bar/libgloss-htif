#include <errno.h>
#include "syscall.h"

int _open(const char *name, int flags, int mode)
{
    errno = ENOENT;
    return -1;
}
