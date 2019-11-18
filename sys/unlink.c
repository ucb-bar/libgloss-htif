#include <errno.h>
#include "syscall.h"

int _unlink(const char *name)
{
    errno = ENOENT;
    return -1;
}
