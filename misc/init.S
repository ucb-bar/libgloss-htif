
    /* Define _init() and _fini() for compatibility */
    .global _init
    .type _init, @function
    .global _fini
    .type _fini, @function
_init:
_fini:
    ret
    .size _init, .-_init
    .size _fini, .-_fini
