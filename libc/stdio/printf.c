#include <stdarg.h>
#include "vxprintf.h"
#include "printbuf.h"
#include "compiler.h"

static void __printf_char(int c, void *arg)
{
    int n = __printbuf_putc(c);
    if (likely(n >= 0)) {
        int *len = arg;
        *len += n;
    }
}

int __wrap_printf(const char *fmt, ...)
{
    va_list ap;
    int len;

    len = 0;
    va_start(ap, fmt);
    __vxprintf(__printf_char, &len, fmt, ap);
    va_end(ap);

    return len;
}
