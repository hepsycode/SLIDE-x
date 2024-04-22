#include <stdint.h>
#include <8051.h>
#include <values.h>

typedef float TARGET_TYPE;
typedef unsigned long TARGET_INDEX;

int8_t i;
TARGET_TYPE y;

/* can3.c - IIR filtering in canonical form, emulating a DSP chip */

TARGET_TYPE can(TARGET_INDEX M, TARGET_TYPE a[M], TARGET_TYPE b[M], TARGET_TYPE w[M], TARGET_TYPE x)                /* usage: y = can3(M, a, b, w, x); */
{

       w[0] = x;                                 /* read input sample */

       for (i=1; i<M; i++)                      /* forward order */
              w[0] -= a[i] * w[i];               /* MAC instruction */

       y = b[M-1] * w[M-1];

       for (i=M-2; i>=0; i--) {                  /* backward order */
              w[i+1] = w[i];                     /* data shift instruction */
              y += b[i] * w[i];                  /* MAC instruction */
       }

       return y;                                 /* output sample */
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
	can(M, a, b, w, x);
	reset_values();
}