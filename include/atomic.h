#ifndef _CHIPYARD_ATOMIC_H
#define _CHIPYARD_ATOMIC_H

#include <stdint.h>

static inline unsigned long local_irq_save(void)
{
    /* Interrupts are currently always disabled in M-mode */
    return 0;
}

static inline void local_irq_restore(unsigned long flags)
{
}

static inline void mb(void)
{
    __asm__ __volatile__ ("fence" ::: "memory");
}

static inline void mb_acquire(void)
{
    __asm__ __volatile__ ("fence r, rw" ::: "memory");
}

static inline void mb_release(void)
{
    __asm__ __volatile__ ("fence rw, w" ::: "memory");
}

typedef volatile int32_t atomic_t;

static inline long atomic_read(const atomic_t *v)
{
    /* FIXME: Elide redundant sext.w for volatile variables */
    long r;
    __asm__ __volatile__ (
        "lw %0, %1"
        : "=r" (r)
        : "A" (*v));
    return r;
}

static inline void atomic_set(atomic_t *v, long n)
{
    *v = n;
}

static inline long atomic_swap_acquire(atomic_t *v, long n)
{
    long r;
#ifdef __riscv_atomic
    __asm__ __volatile__ (
        "amoswap.w.aq %0, %1, %2"
        : "=r" (r)
        : "r" (n), "A" (*v)
        : "memory");
#else
    unsigned long flags;
    flags = local_irq_save();
    r = atomic_read(v);
    atomic_set(v, n);
    local_irq_restore(flags);
#endif
    return r;
}

static inline void atomic_clear_release(atomic_t *v)
{
#ifdef __riscv_atomic
    __asm__ __volatile__ (
        "amoswap.w.rl x0, x0, %0"
        :: "A" (*v) : "memory");
#else
    atomic_set(v, 0);
    mb_release();
#endif
}


#endif /* _CHIPYARD_ATOMIC_H */
