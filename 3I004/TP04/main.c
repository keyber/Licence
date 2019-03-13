#include <stdio.h>

__attribute__((constructor)) void main()
{
    char byte;
    char str[] = "H3110 W0R1D\n";

    while(1){
    	tty_puts(str);
	tty_getc(&byte);
	if(byte == 'q')
		exit();
	}
    exit();
}

