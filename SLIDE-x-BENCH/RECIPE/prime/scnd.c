/* MDH WCET BENCHMARK SUITE. */

#include <stdint.h>
#if (!defined(_GCOV_EXE_))
#include <8051.h>
#endif
#include <values.h>

typedef int64_t TARGET_TYPE;
typedef uint8_t TARGET_INDEX;

TARGET_TYPE i;
TARGET_TYPE quot;

#if (!defined(_GCOV_EXE_))
void resetValues()
{
	P0 = 0;
	P1 = 0;
	P2 = 0;
	P3 = 0;
}
#endif

TARGET_TYPE my_fmod(TARGET_TYPE a, TARGET_TYPE b)
{
    quot = (TARGET_TYPE) a/b;
    return a - (quot * b);
}

TARGET_INDEX divides(TARGET_TYPE n, TARGET_TYPE m)
{
  return (my_fmod(n, m) == 0);
}

TARGET_INDEX even(TARGET_TYPE n)
{
  return (divides (2, n));
}

TARGET_INDEX prime()
{
  if (even(n))
      return (n == 2);

  for (i = 3; 
       i * i <= n;
       i += 2) { 

      if (divides (i, n)) /* ai: loop here min 0 max 357 end; */
          return 0; 
  }

  return (n > 1);
}

void main ()
{
	prime();
  	#if (!defined(_GCOV_EXE_))
	resetValues();
	#endif
}

