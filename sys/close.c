#include <errno.h>
#include "syscall.h"

int _close(int file)
{
    errno = EBADF;
    return -1;
}
