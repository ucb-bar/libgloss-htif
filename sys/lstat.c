#include <errno.h>
#include <sys/stat.h>
#include "syscall.h"

int _lstat(const char *file, struct stat *st)
{
    errno = ENOENT;
    return -1;
}
