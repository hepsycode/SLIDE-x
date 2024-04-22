#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <values.h>

typedef int16_t TARGET_TYPE;
typedef uint16_t TARGET_INDEX;

TARGET_INDEX i, n, k;
TARGET_TYPE *y;

// corr.c - sample cross correlation of two length-N signals 

void corr(TARGET_INDEX M, TARGET_TYPE a[M], TARGET_INDEX L, TARGET_TYPE b[L])            /* computes \(R[k]\), \(k = 0, 1,\dotsc, M\) */
{
	y = malloc((L+M)*sizeof(float));

	for (k=0; k<=L; k++)
		for (y[k]=0, n=0; n<M-k; n++)
			y[k] += a[n+k] * b[n] / M;

}

void main()
{
	corr(M, a, L, b);
}

