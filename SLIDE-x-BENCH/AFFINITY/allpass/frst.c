#include <stdint.h>
#include <values.h>


typedef float TARGET_TYPE;
typedef unsigned long TARGET_INDEX;

TARGET_TYPE y, s0, sD;

/* wrap.c - circular wrap of pointer p, relative to array w */

void wrap(TARGET_INDEX M, TARGET_TYPE w[D], TARGET_TYPE **p)
{
       if (*p > w + M)
              *p -= M + 1;          /* when \(*p=w+M+1\), it wraps around to \(*p=w\) */

       if (*p < w)
              *p += M + 1;          /* when \(*p=w-1\), it wraps around to \(*p=w+M\) */
}

/* cdelay.c - circular buffer implementation of D-fold delay */

void cdelay(TARGET_INDEX D, TARGET_TYPE w[D], TARGET_TYPE **p)
{
       (*p)--;                      /* decrement pointer and wrap modulo-\((D+1)\) */
       wrap(D, w, p);               /* when \(*p=w-1\), it wraps around to \(*p=w+D\) */
}

/* tap.c - i-th tap of circular delay-line buffer */

TARGET_TYPE tap(TARGET_INDEX D, TARGET_TYPE w[D], TARGET_TYPE **p, TARGET_INDEX i) /* usage: si = tap(D, w, p, i); \(p\) passed by value; \(i=0,1,\dotsc, D\) */
{
		//printf("TAP = %f\n", w[(int)(**p - *w + i) % (D + 1)]);
		return w[(TARGET_INDEX)(**p - *w + i) % (D + 1)];
}

/* allpass.c - allpass reverberator with circular delay line */

TARGET_TYPE allpass(TARGET_INDEX D, TARGET_TYPE w[D], TARGET_TYPE a, TARGET_TYPE x)                   /* usage: y=allpass(D,w,&p,a,x); \(p\) is passed by address */
{
	TARGET_TYPE **p; //, p1;

	//p1 = &w;
	p = &w;

       sD = tap(D, w, p, D);                   /* \(D\)th tap delay output */
       s0 = x + a * sD;
       y  = -a * s0 + sD;                       /* filter output */
       **p = s0;                                /* delay input */
       cdelay(D, w, p);                         /* update delay line */

       return y;
}

void main()
{
	allpass(D, w, a, x);
}

