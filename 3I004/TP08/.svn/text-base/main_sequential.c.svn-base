#include <stdio.h>

#define NBLOCS 32
#define THRESHOLD 200

__attribute__((constructor)) void main(void)
{
    char buf_in[128*128];
    char buf_out[128*128];
    unsigned int i;
    unsigned int base = 0;

    while (base < 5 * NBLOCS)
    {

        tty_printf("\n *** image %d *** at date = %d \n",
                base / NBLOCS, proctime());

        /* Phase 1 : lecture image sur le disque et transfert vers buf_in */
        if (ioc_read(/* A COMPLETER */))
        {
            tty_printf("echec io_read\n");
            exit();
        }
        else
        {
            ioc_completed();
            tty_printf("io_read  completed at date = %d \n", proctime());
        }

        /* Phase 2 : transfert de buf_in vers buf_out avec seuillage */
        for (i = 0; i < 128 * 128; i++)
        {
            if (buf_in[i] > THRESHOLD)
                buf_out[i] = 255;
            else
                buf_out[i] = buf_in[i];
        }
        tty_printf("image processing completed at date = %d \n", proctime());

        /* Phase 3 : transfert de buf_out vers le frame buffer par dma */
        if (fb_sync_write(/* A COMPLETER */))
        {
            tty_printf("echec fb_write\n");
            exit();
        }
        else
        {
            tty_printf("transfer completed at date = %d \n", proctime());
        }

        base = base + NBLOCS;
    }

    exit();
}
