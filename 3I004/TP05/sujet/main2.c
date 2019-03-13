#include <stdio.h>

__attribute__((constructor)) void main(void)
{
    unsigned int tab[15];
    unsigned int k;
    unsigned int i;
    char byte;

    for (i = 0; i < 15; i++)
        tab[i] = 0;

    for (k = 0; k < 1000; k++)//tab[i]=1000*i
    {
      for (i = 0; i < 15; i++)
        tab[i] = tab[i]+i;
    }
    for (i = 0; i < 15; i++)
        tty_printf("tab[%d] = %d\n", i, tab[i]);

    tty_getc(&byte);

    exit();
}
