#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <values.h>
#include <8051.h>
#include <math.h>

typedef float TARGET_TYPE;
typedef unsigned long TARGET_INDEX;

TARGET_INDEX i;
TARGET_TYPE *a;

void fib2(TARGET_INDEX n)
{

	a = malloc((n)*sizeof(TARGET_TYPE));

	a[0] = 0;
	a[1] = 1;
	for (i=2 ; i <= n ; i++)
		a[i] = a[i-1] + a[i-2];

	// deallocating the memory
    	free(a);
}

void reset_values()
{
	P0 = 0;
	P1 = 0;
	P2 = 0;
	P3 = 0;
}

void main()
{
	fib2(n);
	reset_values();
}