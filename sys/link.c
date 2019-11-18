#include <errno.h>
#include "syscall.h"

int _link(const char *old_name, const char *new_name)
{
    errno = ENOSYS;
    return -1;
}
