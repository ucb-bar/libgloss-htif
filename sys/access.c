#include <errno.h>
#include "syscall.h"

int _access(const char *file, int mode)
{
    errno = ENOENT;
    return -1;
}
