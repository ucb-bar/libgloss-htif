#include "asm.h"

    .section .text.init

    .macro ENTER func
    /* Default to empty argument vector */
    li a0, 1            /* argc = 1 */
    la a1, argv         /* argv = { "", NULL } */
    LREG a2, environ    /* envp */
    call \func
    tail exit
    .endm

    .global _start_main
    .type _start_main, @function
_start_main:
    BARRIER_PASS __boot_sync
    ENTER main

    .global _start_secondary
    .type _start_secondary, @function
_start_secondary:
    /* Synchronize secondary harts */
    BARRIER_WAIT __boot_sync
    ENTER __main


    .section .rodata
    .align 3
argv:
    .dc.a name
    .dc.a 0
name:
    .asciz "chipyard"

    .bss
__boot_sync:
    .word 0
