#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <values.h>

typedef float TARGET_TYPE;
typedef unsigned long TARGET_INDEX;

TARGET_INDEX i;
int16_t *v, *w;

int max (TARGET_TYPE a, TARGET_TYPE b)
{
  return (a>b?a:b);
}

// dir.c - IIR filtering in direct form

TARGET_TYPE dir(TARGET_INDEX M, TARGET_TYPE a[M], TARGET_INDEX L, TARGET_TYPE b[L], TARGET_TYPE x)           /* usage: y = dir(M, a, L, b, w, v, x); */
{
       w = malloc(max(L,M)*sizeof(int16_t));
       v = malloc(max(L,M)*sizeof(int16_t));

       v[0] = x;                          /* current input sample */
       w[0] = 0;                          /* current output to be computed */

       for (i=0; i<=L; i++)               /* numerator part */
              w[0] += b[i] * v[i];

       for (i=1; i<=M; i++)               /* denominator part */
              w[0] -= a[i] * w[i];

       for (i=L; i>=1; i--)               /* reverse-order updating of \(v\) */
              v[i] = v[i-1];

       for (i=M; i>=1; i--)               /* reverse-order updating of \(w\) */
              w[i] = w[i-1];

       return w[0];                       /* current output sample */
}

void main()
{
	dir(M, a, L, b, x);
}

