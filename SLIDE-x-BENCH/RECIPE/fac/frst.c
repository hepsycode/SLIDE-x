#include <stdint.h>
#include <values.h>

typedef int64_t TARGET_TYPE;
typedef uint8_t TARGET_INDEX;

//void prototype(int8_t n);

  TARGET_INDEX i;
  TARGET_TYPE s = 0;

TARGET_TYPE fac1 (TARGET_TYPE n)
{
  if (n == 0)
     return 1;
  else
     return (n * fac1 (n-1));
}

void fac()
{
  // n = 5;
  for (i = 0;  i <= n; i++)
      s += fac1 (i);
}

void main()
{
	fac();
}