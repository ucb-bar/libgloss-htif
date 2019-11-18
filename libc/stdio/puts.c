#include "printbuf.h"

int __wrap_puts(const char *s)
{
    return __printbuf_puts(s);
}
