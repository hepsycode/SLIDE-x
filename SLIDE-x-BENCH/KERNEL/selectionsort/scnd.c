#include <stdint.h>
#include <8051.h>
#include <values.h>

typedef int8_t TARGET_TYPE;
typedef int8_t TARGET_INDEX;

void selectionsort(TARGET_INDEX size, TARGET_TYPE a[size])
{
  TARGET_INDEX i, j, min_idx = 0;
  TARGET_TYPE temp = 0;

  for(i = 0; i < size-1; i++)
  {

    min_idx = i;
    for(j = i+1; j < size; j++)
      if(a[j] < a[min_idx])
        min_idx = j;
    
      // Swap elements     
      temp = a[min_idx];
      a[min_idx] = a[i];
      a[i] = temp;
    }
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
	selectionsort(size, a);
	reset_values();
}
