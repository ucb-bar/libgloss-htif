#include <errno.h>
#include <sys/stat.h>
#include "syscall.h"

int _fstat(int file, struct stat *st)
{
    errno = EBADF;
    return -1;
}
