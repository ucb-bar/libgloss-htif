#include <errno.h>
#include <sys/stat.h>
#include "syscall.h"

int _fstatat(int dirfd, const char *file, struct stat *st, int flags)
{
    errno = EBADF;
    return -1;
}
