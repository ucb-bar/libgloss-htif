
/*
 * Main function for secondary harts
 * 
 * Multi-threaded programs should provide their own implementation.
 */
void  __attribute__ ((weak,noreturn)) __main(void)
{
    for (;;) {
        __asm__ __volatile__ ("wfi");
    }
}
