#ifndef _CHIPYARD_HTIF_H
#define _CHIPYARD_HTIF_H

#include <stdint.h>

extern volatile uint64_t tohost;
extern volatile uint64_t fromhost;

#define HTIF_DEV_SHIFT      56
#define HTIF_DEV_MASK       0xff
#define HTIF_CMD_SHIFT      48
#define HTIF_CMD_MASK       0xff
#define HTIF_PAYLOAD_MASK   ((1UL << HTIF_CMD_SHIFT) - 1)

#if __riscv_xlen == 64
#define HTIF_TOHOST(dev, cmd, payload) ( \
    (((uint64_t)(dev) & HTIF_DEV_MASK) << HTIF_DEV_SHIFT) | \
    (((uint64_t)(cmd) & HTIF_CMD_MASK) << HTIF_CMD_SHIFT) | \
    ((uint64_t)(payload) & HTIF_PAYLOAD_MASK))
#else
/* HTIF devices not supported on RV32 */
#define HTIF_TOHOST(dev, cmd, payload) \
    (((dev) || (cmd)) ? (__builtin_trap(), 0) : (payload))
#endif

extern long htif_syscall(uint64_t, uint64_t, uint64_t, unsigned long);

#endif /* _CHIPYARD_HTIF_H */
