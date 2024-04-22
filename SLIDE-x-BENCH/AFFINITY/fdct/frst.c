#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <values.h>
#include <math.h>

#ifndef PI
# ifdef M_PI
#  define PI M_PI
# else
#  define PI 3.14159265358979323846
# endif
#endif

typedef float TARGET_TYPE;
typedef unsigned long TARGET_INDEX;

TARGET_INDEX i, j, k;

static double c[8][8] = {{0.353553, 0.353553, 0.353553, 0.353553, 0.353553, 0.353553, 0.353553, 0.353553},
{0.490393, 0.415735, 0.277785, 0.097545, -0.097545, -0.277785, -0.415735, -0.490393},
{0.461940, 0.191342, -0.191342, -0.461940, -0.461940, -0.191342, 0.191342, 0.461940},
{0.415735, -0.097545, -0.490393, -0.277785, 0.277785, 0.490393, 0.097545, -0.415735},
{0.353553, -0.353553, -0.353553, 0.353553, 0.353553, -0.353553, -0.353553, 0.353553},
{0.277785, -0.490393, 0.097545, 0.415735, -0.415735, -0.097545, 0.490393, -0.277785},
{0.191342, -0.461940, 0.461940, -0.191342, -0.191342, 0.461940, -0.461940, 0.191342},
{0.097545, -0.277785, 0.415735, -0.490393, 0.490393, -0.415735, 0.277785, -0.097545}}; /* transform coefficients */

void fdct(TARGET_INDEX M, TARGET_TYPE a[M])
{
	  double s;
	  double tmp[64];

	for (i=0; i<8; i++)
		for (j=0; j<8; j++)
		{
			s = 0.0;

			for (k=0; k<8; k++)
				s += c[j][k] * a[8*i+k];
			tmp[8*i+j] = s;
		}

	for (j=0; j<8; j++)
		for (i=0; i<8; i++)
		{
			s = 0.0;

			for (k=0; k<8; k++)
				s += c[i][k] * tmp[8*k+j];

			a[8*i+j] = (TARGET_TYPE) floor(s+0.499999);
			/*
			* reason for adding 0.499999 instead of 0.5:
			* s is quite often x.5 (at least for i and/or j = 0 or 4)
			* and setting the rounding threshold exactly to 0.5 leads to an
			* extremely high arithmetic implementation dependency of the result;
			* s being between x.5 and x.500001 (which is now incorrectly rounded
			* downwards instead of upwards) is assumed to occur less often
			* (if at all)
			*/
		}
}

void main()
{
	fdct(M, a);
}

