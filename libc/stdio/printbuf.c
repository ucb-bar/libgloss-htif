#include "printbuf.h"

__thread char __printbuf[128] __aligned(64);
__thread size_t __printbuflen = 0;
