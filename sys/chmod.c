#include <errno.h>
#include <sys/types.h>
#include "syscall.h"

int _chmod(const char *path, mode_t mode)
{
    errno = ENOSYS;
    return -1;
}
