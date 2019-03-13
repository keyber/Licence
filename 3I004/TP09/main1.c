#include <stdio.h>

__attribute__((constructor)) void main1(void)
{
    unsigned int opx;
    unsigned int res;
    unsigned int i;

    tty_puts(" TASK 1 : FACTORIELLE \n");

    while (1)
    {
        tty_puts("\n*********************\n");
        tty_puts("operand  = ");
        tty_getw_irq(&opx);
        tty_puts("\n");
        if ((opx > 12) || (opx < 1))
        {
            tty_puts("operand must be larger than 0 and smaller than 13\n");
        } else {
            res = 1;
            for (i = opx; i > 1; i--)
                res = res*i;
            tty_printf("factorielle(%d) = %d\n", opx, res);
        }
    }

    exit();
}
