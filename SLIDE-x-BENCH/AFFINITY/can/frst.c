#include <stdint.h>
#include <values.h>

typedef int8_t TARGET_TYPE;
typedef uint8_t TARGET_INDEX;

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


void main()
{
	can(m, a, b, w, x);
}

