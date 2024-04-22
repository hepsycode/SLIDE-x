#include <stdint.h>
#include <values.h>

typedef float TARGET_TYPE;
typedef unsigned long TARGET_INDEX;

TARGET_TYPE **p;

/* wrap.c - circular wrap of pointer p, relative to array w */

void wrap(TARGET_INDEX D, TARGET_TYPE w[D], TARGET_TYPE a)
{
	p = &a; 
       if (*p > w + D)
              *p -= D + 1;          /* when \(*p=w+M+1\), it wraps around to \(*p=w\) */

       if (*p < w)
              *p += D + 1;          /* when \(*p=w-1\), it wraps around to \(*p=w+M\) */
}

void main()
{
	wrap(D, w, a);                         /* update delay line */
}

