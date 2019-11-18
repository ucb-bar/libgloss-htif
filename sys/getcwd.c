#include <stddef.h>
#include <errno.h>
#include "syscall.h"

char *_getcwd(char *buf, size_t size)
{
    errno = ENOSYS;
    return NULL;
}
