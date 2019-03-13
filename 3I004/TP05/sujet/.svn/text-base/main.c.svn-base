#include <stdio.h>

__attribute__((constructor)) void main(void)
{
    unsigned int tab[15];
    unsigned int k;
    unsigned int i;
    char byte;

    for (i = 0; i < 15; i++)
        tab[i] = 0;

    for (k = 0; k < 1000; k++)
    {
        tab[0]  = tab[0]  + 0;
        tab[1]  = tab[1]  + 1;
        tab[2]  = tab[2]  + 2;
        tab[3]  = tab[3]  + 3;
        tab[4]  = tab[4]  + 4;
        tab[5]  = tab[5]  + 5;
        tab[6]  = tab[6]  + 6;
        tab[7]  = tab[7]  + 7;
        tab[8]  = tab[8]  + 8;
        tab[9]  = tab[9]  + 9;
        tab[10] = tab[10] + 10;
        tab[11] = tab[11] + 11;
        tab[12] = tab[12] + 12;
        tab[13] = tab[13] + 13;
        tab[14] = tab[14] + 14;
    }

    for (i = 0; i < 15; i++)
        tty_printf("tab[%d] = %d\n", i, tab[i]);

    tty_getc(&byte);

    exit();
}
