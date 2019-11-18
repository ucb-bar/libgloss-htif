#include <errno.h>
#include "syscall.h"

int _wait(int *status)
{
    errno = ECHILD;
    return -1;
}
