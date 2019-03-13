#include <stdio.h>

__attribute__((constructor)) void main2(void)
{
    unsigned int opx;
    unsigned int opy;
    unsigned int x;
    unsigned int y;

    tty_puts(" TASK 2 : PGCD \n");

    while (1)
    {
        tty_puts("\n*******************\n");
        tty_puts("operand X = ");
        tty_getw_irq(&opx);
        tty_puts("\n");
        tty_printf("operand Y = ");
        tty_getw_irq(&opy);
        tty_puts("\n");

        if ((opx == 0) || (opy == 0))
        {
            tty_puts("operands must be larger than 0\n");
        }
        else
        {
            x = opx;
            y = opy;
            while (x != y)
            {
                if (x > y)
                    x = x - y;
                else
                    y = y - x;
            }
            tty_printf("pgcd(%d, %d) = %d\n", opx, opy, x);
        }
    }

    exit();
}
