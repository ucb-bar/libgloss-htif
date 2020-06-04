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


#define fence(p, s) \
    __asm__ __volatile__ ("fence " #p ", " #s : : : "memory")

static inline void mb(void) { fence(rw, rw); }
static inline void rmb(void) { fence(r, r); }
static inline void wmb(void) { fence(w, w); }
static inline void mb_acquire(void) { fence(r, rw); }
static inline void mb_release(void) { fence(rw, w); }


typedef int32_t atomic_t;

static inline long atomic_load(const atomic_t *p)
{
    /* FIXME: Elide redundant sext.w for volatile variables */
    return *((volatile const atomic_t *)p);
}

static inline void atomic_store(atomic_t *p, atomic_t v)
{
    *((volatile atomic_t *)p) = v;
}

static inline long atomic_swap_acquire(atomic_t *p, atomic_t v)
{
    long n;
#ifdef __riscv_atomic
    __asm__ __volatile__ (
        "amoswap.w.aq %0, %1, %2"
        : "=r" (n)
        : "r" (v), "A" (*p)
        : "memory");
#else
    unsigned long flags;
    flags = local_irq_save();
    n = atomic_load(p);
    atomic_store(p, v);
    local_irq_restore(flags);
    mb();
#endif
    return n;
}

static inline void atomic_clear_release(atomic_t *p)
{
#ifdef __riscv_atomic
    __asm__ __volatile__ (
        "amoswap.w.rl x0, x0, %0"
        :
        : "A" (*p)
        : "memory");
#else
    mb_release();
    atomic_store(p, 0);
#endif
}

#endif /* _CHIPYARD_ATOMIC_H */
