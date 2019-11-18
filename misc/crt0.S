#include "encoding.h"

#if __riscv_xlen == 64
# define LREG ld
# define SREG sd
# define REGBYTES 8
#else
# define LREG lw
# define SREG sw
# define REGBYTES 4
#endif

    .section .text.init
    .global _start
    .type _start, @function
_start:
    .cfi_startproc

    li x1, 0
    li x2, 0
    li x3, 0
    li x4, 0
    li x5, 0
    li x6, 0
    li x7, 0
    li x8, 0
    li x9, 0
    li x10, 0
    li x11, 0
    li x12, 0
    li x13, 0
    li x14, 0
    li x15, 0
    li x16, 0
    li x17, 0
    li x18, 0
    li x19, 0
    li x20, 0
    li x21, 0
    li x22, 0
    li x23, 0
    li x24, 0
    li x25, 0
    li x26, 0
    li x27, 0
    li x28, 0
    li x29, 0
    li x30, 0
    li x31, 0

    li t0, (MSTATUS_FS | MSTATUS_XS)
    csrs mstatus, t0

    /* Initialize global pointer; disable relaxation to avoid relaxing
       the address calculation to "addi gp, gp, 0" */
    .option push
    .option norelax
    la gp, __global_pointer$
    .option pop

    /* Initialize thread pointer */
    csrr s0, mhartid
    lui t0, %hi(__stack_shift)
    addi t0, t0, %lo(__stack_shift)
    la tp, __stack_start
    sll t0, s0, t0
    add tp, tp, t0

    /* Initialize stack pointer */
    lui t0, %hi(__stack_size)
    addi t0, t0, %lo(__stack_size)
    add sp, tp, t0

    /* Initialize TLS */
    call __init_tls

    /* Skip global initialization if not the designated boot hart */
    la t0, __boot_hart
    la s1, __boot_sync
    bne s0, t0, 1f

    /* Call global constructors */
    la a0, __libc_fini_array
    call atexit
    call __libc_init_array

    /* Set __boot_sync flag */
    li t0, -1
    sw t0, (s1)

    .macro enter func
    li a0, 1    /* argc = 1 */
    la a1, argv /* argv = { "chipyard", NULL } */
    la a2, envp /* envp = { NULL } */
    call \func
    tail exit
    .endm

    enter main

1:  /* Synchronize secondary harts */
    lw t0, (s1)
    beqz t0, 1b
    enter __main

    .cfi_endproc

    .section .rodata
    .align 3
argv:
    .dc.a name
envp:
    .dc.a 0
name:
    .asciz "chipyard"

    .section .data
    .align 2
__boot_sync:
    .word 0
