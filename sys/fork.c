#include <errno.h>
#include "syscall.h"

int _fork(void)
{
    errno = EAGAIN;
    return -1;
}
