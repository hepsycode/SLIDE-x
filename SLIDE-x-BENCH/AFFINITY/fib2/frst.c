#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <values.h>
#include <math.h>

typedef int32_t TARGET_TYPE;
typedef uint32_t TARGET_INDEX;

TARGET_INDEX i;
TARGET_TYPE *a;

void fib2(TARGET_INDEX n)
{

	a = malloc((n)*sizeof(int16_t));

	a[0] = 0;
	a[1] = 1;
	for (i=2 ; i <= n ; i++)
		a[i] = a[i-1] + a[i-2];

	// deallocating the memory
    	free(a);
}

void main()
{
	fib2(n);
}

