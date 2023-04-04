#include "leesInteger.h"

#include <stdio.h>
#include <stdlib.h>

#define READ_INTEGER_FROM_CONSOLE

/*
 * DO NOT ADAPT THE FOLLOWING CODE!!!!
 */

int leesInteger()
{
#ifdef READ_INTEGER_FROM_CONSOLE
	char text[80];

    //printf( "geef int waarde: " );
	return atoi( fgets(text,80,stdin) );
#else
    int waarde = 1 + ( rand() % 100 );
    printf( "int waarde: %3d\n", waarde );
    return waarde;
#endif
}
