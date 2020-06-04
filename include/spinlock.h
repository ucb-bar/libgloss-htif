#ifndef _CHIPYARD_SPINLOCK_H
#define _CHIPYARD_SPINLOCK_H

#include "atomic.h"

typedef struct {
    atomic_t lock;
} spinlock_t;

#define SPINLOCK_INIT { 0U }

static inline void spin_lock(spinlock_t *lock)
{
    do {
#ifdef __riscv_atomic
        while (atomic_load(&lock->lock));
#endif
    } while (atomic_swap_acquire(&lock->lock, -1));
}

static inline void spin_unlock(spinlock_t *lock)
{
    atomic_clear_release(&lock->lock);
}

#endif /* _CHIPYARD_SPINLOCK_H */
