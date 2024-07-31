#include <stdint.h>
#include <8051.h>
#include <values.h>

typedef float TARGET_TYPE;
typedef unsigned long TARGET_INDEX;

int8_t i;
TARGET_TYPE y;

/* can3.c - IIR filtering in canonical form, emulating a DSP chip */

TARGET_TYPE can(TARGET_INDEX m, TARGET_TYPE a[m], TARGET_TYPE b[m], TARGET_TYPE w[m], TARGET_TYPE x)                /* usage: y = can3(m, a, b, w, x); */
{

       w[0] = x;                                 /* read input sample */

       for (i=1; i<m; i++)                      /* forward order */
              w[0] -= a[i] * w[i];               /* mAC instruction */

       y = b[m-1] * w[m-1];

       for (i=m-2; i>=0; i--) {                  /* backward order */
              w[i+1] = w[i];                     /* data shift instruction */
              y += b[i] * w[i];                  /* mAC instruction */
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
	can(m, a, b, w, x);
	reset_values();
}