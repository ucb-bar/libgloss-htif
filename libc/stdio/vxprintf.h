#ifndef _CHIPYARD_VXPRINTF_H
#define _CHIPYARD_VXPRINTF_H

#include <stdarg.h>

typedef void (*putc_t)(int, void *);

extern void __vxprintf(putc_t, void *, const char *, va_list);

#endif /* _CHIPYARD_VXPRINTF_H */
