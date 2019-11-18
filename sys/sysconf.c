#include <unistd.h>
#include "syscall.h"
#include "encoding.h"

long _sysconf(int name)
{
    switch (name) {
    case _SC_PAGE_SIZE:
        return RISCV_PGSIZE;
    }
    return -1;
}
