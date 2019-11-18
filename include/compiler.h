#ifndef _CHIPYARD_COMPILER_H
#define _CHIPYARD_COMPILER_H

#ifndef __ASSEMBLY__

#define likely(x)   __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

#endif /* !__ASSEMBLY __*/

#endif /* _CHIPYARD_COMPILER_H */
