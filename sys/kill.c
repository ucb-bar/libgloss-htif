#include <errno.h>
#include "syscall.h"

int _kill(int pid, int sig)
{
    errno = EINVAL;
    return -1;
}
