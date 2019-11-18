#include <string.h>

void __init_tls(void)
{
    register char *__thread_self __asm__ ("tp");
    extern char __tdata_start[];
    extern char __tbss_offset[];
    extern char __tdata_size[];
    extern char __tbss_size[];

    memcpy(__thread_self, __tdata_start, (size_t)__tdata_size);
    memset(__thread_self + (size_t)__tbss_offset, 0, (size_t)__tbss_size);
}
