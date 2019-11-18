#include <stddef.h>
#include <stdarg.h>
#include "vxprintf.h"
#include "compiler.h"

struct snprintf {
    char *str;
    char *end;
};

static void __snprintf_putc(int c, void *arg)
{
    struct snprintf *data = arg;
    if (likely(data->str < data->end)) {
        *(data->str)++ = c;
    }
}

int __wrap_snprintf(char *str, size_t size, const char *fmt, ...)
{
    va_list ap;
    struct snprintf data;

    if (unlikely(size <= 0))
        return 0;

    data.str = str;
    data.end = str + size - 1;

    va_start(ap, fmt);
    __vxprintf(__snprintf_putc, &data, fmt, ap);
    va_end(ap);

    *(data.str) = '\0';
    return data.str - str;
}
