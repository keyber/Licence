#include <stdio.h>

__attribute__((constructor)) void main(void)
{
    unsigned int i;
    char byte;

    for (i = 0; i < 1000; i++)
    {
        if (tty_printf(" hello %d\n", procid()))
        {
            tty_puts("echec tty_printf\n");
            exit();
        }
        tty_getc_irq((void*)&byte);

        if (byte == 'q')
            exit();
    }

    exit();
}

