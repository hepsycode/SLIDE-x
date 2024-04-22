#include <stdint.h>
#include <values.h>

typedef int8_t TARGET_TYPE;
typedef int8_t TARGET_INDEX;

TARGET_TYPE **p;

/* tap.c - i-th tap of circular delay-line buffer */

TARGET_TYPE tap(TARGET_INDEX D, TARGET_TYPE w[D], TARGET_INDEX x) /* usage: si = tap(D, w, p, i); \(p\) passed by value; \(i=0,1,\dotsc, D\) */
{
	p = &w;
	//printf("TAP = %f\n", w[(int)(**p - *w + i) % (D + 1)]);
	return w[(TARGET_INDEX)(**p - *w + x) % (D + 1)];
}

void main()
{
	tap(D, w, D);                   /* \(D\)th tap delay output */
}

