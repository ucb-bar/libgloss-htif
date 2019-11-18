#ifndef _CHIPYARD_SYSCALL_H
#define _CHIPYARD_SYSCALL_H

#include <stddef.h>
#include <sys/types.h>

#include "htif.h"

/* Frontend system calls supported by fesvr */
#define SYS_getcwd 17
#define SYS_fcntl 25
#define SYS_mkdirat 34
#define SYS_unlinkat 35
#define SYS_linkat 37
#define SYS_renameat 38
#define SYS_ftruncate 46
#define SYS_faccessat 48
#define SYS_chdir 49
#define SYS_openat 56
#define SYS_close 57
#define SYS_lseek 62
#define SYS_read 63
#define SYS_write 64
#define SYS_pread 67
#define SYS_pwrite 68
#define SYS_fstatat 79
#define SYS_fstat 80
#define SYS_exit 93
#define SYS_lstat 1039
#define SYS_getmainvars 2011


#define __SYSCALL_NARGS_X(a,b,c,d,e,f,g,...) g
#define __SYSCALL_NARGS(...) \
    __SYSCALL_NARGS_X(__VA_ARGS__,6,5,4,3,2,1,0,)

#define __SYSCALL_CONCAT_X(a, b) a ## b
#define __SYSCALL_CONCAT(a, b) __SYSCALL_CONCAT_X(a, b)

#define __SYSCALL(n, ...) \
    __SYSCALL_CONCAT(__syscall, __SYSCALL_NARGS(__VA_ARGS__))(n, __VA_ARGS__)

static inline uintptr_t __syscall3(uint64_t num, uint64_t arg0, uint64_t arg1, uint64_t arg2)
{
    volatile uint64_t buf[8];
    buf[0] = num;
    buf[1] = arg0;
    buf[2] = arg1;
    buf[3] = arg2;
    htif_syscall((uintptr_t)buf);
    return buf[0];
}


struct stat;
struct timespec;
struct timeval;
struct timeb;
struct tms;
struct utimbuf;

extern ssize_t _read(int, void *, size_t);
extern ssize_t _write(int, const void *, size_t);
extern int _open(const char *, int, int);
extern int _close(int);
extern int _stat(const char *, struct stat *);
extern int _lstat(const char *, struct stat *);
extern int _fstat(int, struct stat *);
extern off_t _lseek(int, off_t, int);
extern void *_sbrk(ptrdiff_t);
extern int _access(const char *, int);
extern int nanosleep(const struct timespec *, struct timespec *);
extern int _getpid(void);
extern int _fork(void);
extern int _execve(const char *, char *const [], char *const []);
extern void _exit(int);
extern int _wait(int *);
extern int _kill(int, int);
extern char *_getcwd(char *, size_t);
extern int _chdir(const char *);
extern int _link(const char *, const char *);
extern int _unlink(const char *);
extern int _chmod(const char *, mode_t);
extern int _chown(const char *, uid_t, gid_t);
extern int _gettimeofday(struct timeval *, void *);
extern clock_t _times(struct tms *);
extern int _openat(int, const char *, int, int);
extern int _fstatat(int, const char *, struct stat *, int);
extern int _faccessat(int, const char *, int, int);
extern int _ftime(struct timeb *);
extern int _utime(const char *, const struct utimbuf *);
extern long _sysconf(int);
extern int _isatty(int);

#endif /* _CHIPYARD_SYSCALL_H */
