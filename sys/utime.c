#include <errno.h>
#include <sys/types.h>
#include <utime.h>
#include "syscall.h"

int _utime(const char *path, const struct utimbuf *times)
{
    errno = ENOENT;
    return -1;
}
