#include <stdint.h>
#include <8051.h>
#include <values.h>

typedef int64_t TARGET_TYPE;
typedef uint8_t TARGET_INDEX;

void swap(TARGET_INDEX index_1, TARGET_INDEX index_2)
{
	TARGET_TYPE b = a[index_1];
	a[index_1] = a[index_2];
	a[index_2] = b;
}

void bsort100(TARGET_INDEX size, TARGET_TYPE a[size])
{
	TARGET_INDEX i;
	TARGET_TYPE j;
	TARGET_TYPE is_sorted;
	TARGET_TYPE currentSwap; 
	TARGET_TYPE lastSwap = size-1;

	for(j = 0;
		j < size;
		j++)
	{
		is_sorted = (TARGET_TYPE) 1;
		currentSwap = -1;
		for(i = 0;
			i < lastSwap;
			i++)
		{
			if(a[i] > a[i+1])
			{
				swap(i,i+1);
				is_sorted = 0;
				currentSwap = i;
			}
		}

		if(is_sorted) break;
		lastSwap = currentSwap;
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
	bsort100(size, a);
	reset_values();
}
