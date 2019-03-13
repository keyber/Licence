#include <stdio.h>

#define NPIXELS 128
#define NLINES  128
#define NORM    46
#define RANGE   9

unsigned int input[NLINES][NPIXELS];
unsigned int output[NLINES][NPIXELS];

unsigned int kernel[9] = {1, 2, 4, 8, 16, 8, 4, 2, 1};

void filter(unsigned int line)
{
    int p;
    int k;
    int x;
    int accu;

    for (p = 0; p < NPIXELS; p++)
    {
        accu = 0;
        for (k = 0; k < RANGE; k++)
        {
            if ((p - k) < 0)
                x = 0;
            else if ((p - k) >= (NPIXELS - 1))
                x = NPIXELS - 1;
            else
                x = p - k;
            accu += (input[line][x] * kernel[k]);
        }
        output[line][p] = accu/NORM;
    }
}

__attribute__((constructor)) void main(void)
{
    unsigned int nb_procs = procnumber();
    unsigned int my_index = procid();
    unsigned int time;
    unsigned int line;

    tty_printf("processor %d/%d is alive!\n\n", my_index, nb_procs);

    for (line = 0; line < NLINES; ++line)
    {
            time = proctime();
	    if (line % nb_procs == my_index){
            	tty_printf("processor %d processing line %d at time %d\n", my_index, line, time);
	            filter(line);
	    }
    }

    tty_printf("\nprocessor %d completed at time %d\n", my_index, time);

    exit();
}
