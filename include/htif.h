#ifndef _CHIPYARD_HTIF_H
#define _CHIPYARD_HTIF_H

#include <stdint.h>

extern volatile uint64_t tohost;
extern volatile uint64_t fromhost;

extern void htif_syscall(uintptr_t arg);

#endif /* _CHIPYARD_HTIF_H */
