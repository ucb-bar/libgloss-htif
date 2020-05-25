#include "asm.h"
#include "syscall.h"

/* Maximum number of command-line arguments */
#ifdef ARG_MAX
#if ARG_MAX <= 0
#error "ARG_MAX must be greater than zero"
#endif
#else
#define ARG_MAX 256
#endif

    .section .text.init

    .global _start_main_argv
    .type _start_main_argv, @function
_start_main_argv:
    /* Retrieve argument vector from frontend server */
    addi sp, sp, -(ARG_MAX*8)
    li a3, SYS_getmainvars
    li a1, (ARG_MAX*8)
    mv a0, sp
    call htif_syscall
    bnez a0, 1f

    lw a0, 0(sp)        /* argc = buf[0] */
    addi a1, sp, 8      /* argv = buf + 1 */
    sw a0, argc, t0
    SREG a1, argv, t0

    BARRIER_PASS __boot_sync

    LREG a2, environ    /* envp */
    call main
1:
    tail exit


    .global _start_secondary_argv
    .type _start_secondary_argv, @function
_start_secondary_argv:
    /* Synchronize secondary harts */
    BARRIER_WAIT __boot_sync

    lw a0, argc
    LREG a1, argv
    LREG a2, environ
    call __main
    tail exit


    .bss
    .align 3
argv:
    .dc.a 0
argc:
    .word 0
__boot_sync:
    .word 0
