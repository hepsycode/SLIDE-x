// This functions has been taken from "Numerical Recipes in C" book, Cap 8.1, pag 332
#include <stdint.h>
#include <values.h>

typedef float TARGET_TYPE;
typedef int8_t TARGET_INDEX;

void shell_sort(TARGET_INDEX size, TARGET_TYPE arr[size])
// Sorts an array a[] into ascending numerical order by Shell’s method (diminishing increment
// sort). a is replaced on output by its sorted rearrangement. Normally, the argument n should
// be set to the size of array a , but if n is smaller than this, then only the first n elements of a
// are sorted. This feature is used in selip .
{ 
	TARGET_INDEX i = 0, j = 0;
	TARGET_TYPE v = 0;
	int inc = 1;
	
	// Determine the starting increment.
	do 
	{
		inc *= 3;
		inc++;
	} while (inc <= size);

	do 
	{
		// Loop over the partial sorts.
		inc /= 3;

		for(i = ++inc;
			i < size;
			i++)
			{
			// Outer loop of straight insertion.
			v = arr[i];
			j = i;

			while(arr[j-inc] > v)
			{
				// Inner loop of straight insertion.
				arr[j] = arr[j-inc];
				j -= inc;

				if(j < inc) 
					break;
			}

			arr[j] = v;
		}

	} while (inc > 1);
}


void main()
{	
	shell_sort(size, arr);
}