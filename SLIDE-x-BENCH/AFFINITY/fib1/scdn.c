#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <values.h>
#include <8051.h>
#include <math.h>

typedef int32_t TARGET_TYPE;
typedef uint32_t TARGET_INDEX;

TARGET_INDEX i, f1 = 0, f2 = 1;
TARGET_TYPE *f;

void fib1(TARGET_INDEX n)
{

	f = malloc((n)*sizeof(int16_t));

	f[0] = 0;

	switch (n) {
		case 0: f[0] = 0; break;
		case 1: f[0] = 0; f[1] = 1; break;
		default:
		for (i=2, f[i-2]=0, f[i-1]=1; i <= n ; i++) {
			f[i] = f1 + f2;
			f1 = f2;
			f2 = f[i];
		}
	}
	// deallocating the memory
    	free(f);
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
	fib1(n);
	reset_values();
}