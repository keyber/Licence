#include <stdio.h>

__attribute__((constructor)) void main0(void)
{
    char buf;

    tty_printf(" TASK 0 :  CYCLE COUNT \n");

    while (1)
    {
        tty_getc_irq(&buf);
        tty_printf("\n**** cycle = %d \n", proctime());
    }

    exit();
}
