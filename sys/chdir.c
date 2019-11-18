#include <errno.h>
#include "syscall.h"

int _chdir(const char *path)
{
    errno = ENOSYS;
    return -1;
}
