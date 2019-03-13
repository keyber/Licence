#include <stdio.h>

#define NBLOCS 32
#define THRESHOLD 200

static inline void load_image(unsigned int index, char *buf)
{
    if (ioc_read(index * NBLOCS, buf, NBLOCS))
    {
        tty_printf("echec ioc_read for image %d\n", index);
        exit();
    }
}

static inline void modif_image(unsigned int index, char *buf_in, char *buf_out)
{
    unsigned int i;
    for (i = 0; i < 128 * 128; i++)
    {
        if (buf_in[i] > THRESHOLD)
            buf_out[i] = 255;
        else
            buf_out[i] = buf_in[i];
    }
}

static inline void display_image(unsigned int index, char *buf)
{
    if (fb_write(0, buf, 128 * 128))
    {
        tty_printf("echec fb_write for image %d\n", index);
        exit();
    }
}

__attribute__((constructor)) void main(void)
{
    char buf_in_0[128 * 128];
    char buf_in_1[128 * 128];
    char buf_out_0[128 * 128];
    char buf_out_1[128 * 128];

    /* Macro-period 0 */
    tty_printf("\n *** macro-period 0 at date = %d \n", proctime());
    load_image(0, buf_in_0);
    ioc_completed();

    /* Macro-period 1 */
    tty_printf("\n *** macro-period 1 at date = %d \n", proctime());
    load_image(1, buf_in_1);
    modif_image(0, buf_in_0, buf_out_0);
    ioc_completed();

    /* Macro-preriod 2 */
    tty_printf("\n *** macro-period 2 at date = %d \n", proctime());
    load_image(2, buf_in_0);
    display_image(0, buf_out_0);
    modif_image(1, buf_in_1, buf_out_1);
    fb_completed();
    ioc_completed();

    /* Macro-period 3 */
    tty_printf("\n *** macro-period 3 at date = %d \n", proctime());
    load_image(3,buf_in_1);
    display_image(1, buf_out_1);
    modif_image(2, buf_in_0, buf_out_0);
    fb_completed();
    ioc_completed();

    /* Macro-period 4 */
    tty_printf("\n *** macro-period 4 at date = %d \n", proctime());
    load_image(4,buf_in_0);
    display_image(2, buf_out_0);
    modif_image(3, buf_in_1, buf_out_1);
    fb_completed();

    /* Macro-period 5 */
    tty_printf("\n *** macro-period 5 at date = %d \n", proctime());
    display_image(3, buf_out_1);
    modif_image(4, buf_in_0, buf_out_0);
    fb_completed();

    /* Macro-period 6 */
    tty_printf("\n *** macro-period 6 at date = %d \n", proctime());
    display_image(4, buf_out_0);
    fb_completed();

    /* End of program */
    tty_printf("\n *** end of program at date = %d \n", proctime());
    exit(0);
}

