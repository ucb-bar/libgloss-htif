#include <errno.h>
#include "syscall.h"

int _execve(const char *name, char *const argv[], char *const env[])
{
    errno = ENOMEM;
    return -1;
}
