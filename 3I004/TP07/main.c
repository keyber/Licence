#include <stdio.h>

__attribute__((constructor)) void main(void)
{
    unsigned int i;

    /* A COMPLETER */

    for (i = 0; i < 1000; i++)
    {
        if (tty_printf(" hello world : %d\n",i))
        {
            tty_puts("echec tty_printf\n");
            exit();
        }
    }

    exit();
}

