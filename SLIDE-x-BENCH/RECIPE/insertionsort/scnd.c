#include <stdint.h>
#if (!defined(_GCOV_EXE_))
#include <8051.h>
#endif
#include <values.h>

typedef float TARGET_TYPE;
typedef uint8_t TARGET_INDEX;

void insertionsort(TARGET_INDEX size, TARGET_TYPE a[size])
{
    TARGET_INDEX i = 0;
    TARGET_TYPE temp;
    int j = 0;

    for(i = 1; i < size; i++)
    {

        temp = a[i];
        j = i-1;

        while(j >= 0 && temp < a[j])
        {
            a[j+1] = a[j];
            j = j-1;
        }

        a[j+1] = temp;
    }
}

#if (!defined(_GCOV_EXE_))
void reset_values()
{
  P0 = 0;
  P1 = 0;
  P2 = 0;
  P3 = 0;
}
#endif

void main()
{
	insertionsort(size, a);
	#if (!defined(_GCOV_EXE_))
	reset_values();
	#endif
}
