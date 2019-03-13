#include <stdio.h>

#define NBLOCS 32

__attribute__((constructor)) int main(void)
{
    unsigned char buf[128*128];
    unsigned int  x;
    unsigned int  base = 0;

    while (base < 10 * NBLOCS)
    {
        giet_tty_printf("\n *** image %d *** at date = %d \n",
                base / NBLOCS, giet_proctime());

        /* Phase 1 : lecture image sur le disque et transfert vers buf */
        x = giet_ioc_read(base, buf, NBLOCS);
        if ( x )
        {
            giet_tty_printf("echec giet_ioc_read %d at date : %d\n", x , giet_proctime() );
            giet_exit();
        }
        x = giet_ioc_completed();
        if ( x )
        {
            giet_tty_printf("echec giet_ioc_completed %d at date : %d\n", x, giet_proctime() );
            giet_exit();
        }
        giet_tty_printf("ioc_read  completed at date = %d \n", giet_proctime());

        // Phase 2 : transfert de buf vers le frame buffer par dma 
        x = giet_fb_write(0, buf, 128 * 128);
        if ( x )
        {
            giet_tty_printf("echec giet_fb_write %d at date : %d\n", x, giet_proctime() );
            giet_exit();
        }

        giet_tty_printf("fb_write ok at date : %d\n", giet_proctime() );

        x = giet_fb_completed();
        if ( x )
        {
            giet_tty_printf("echec giet_fb_completed %d at date : %d\n", x, giet_proctime() );
            giet_exit();
        }
        giet_tty_printf("display completed at date = %d \n", giet_proctime());

        base = base + NBLOCS;
    }

    giet_exit();

    return 0;
}
