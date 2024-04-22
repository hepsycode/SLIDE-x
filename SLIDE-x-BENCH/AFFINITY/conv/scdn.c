#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <8051.h>
#include <values.h>

typedef float TARGET_TYPE;
typedef unsigned long TARGET_INDEX;

TARGET_INDEX i, n, m;
TARGET_TYPE *y;

// conv.c - convolution of x[n] with h[n], resulting in y[n]

TARGET_INDEX min (TARGET_INDEX a, TARGET_INDEX b)
{
  return (a>b?b:a);
}

TARGET_INDEX max (TARGET_INDEX a, TARGET_INDEX b)
{
  return (a>b?a:b);
}

void conv(TARGET_INDEX M, TARGET_TYPE a[M], TARGET_INDEX L, TARGET_TYPE b[L])           /* usage: y = dir(M, a, L, b, w, v, x); */
{
	y = malloc((L+M)*sizeof(TARGET_TYPE));

	for (n = 0; n < L+M; n++){
		y[n] = 0;
		for (m = max(0, n-L+1); m <= min(n, M); m++){
			 y[n] += a[m] * b[n-m];
		}
	}
	free(y);

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
	conv(M, a, L, b);
	reset_values();
}