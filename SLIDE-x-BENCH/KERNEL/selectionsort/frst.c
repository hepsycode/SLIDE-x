#include <stdint.h>
#include <values.h>

typedef double TARGET_TYPE;
typedef uint8_t TARGET_INDEX;

void selectionsort()
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

void main()
{
  selectionsort();
}
