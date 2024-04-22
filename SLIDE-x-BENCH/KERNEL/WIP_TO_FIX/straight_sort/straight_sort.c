// This functions has been taken from "Numerical Recipes in C" book, Cap 8.1, pag 330
#include <stdint.h>
#include <values.h>

typedef float TARGET_TYPE;
typedef int8_t TARGET_INDEX;

void straight_sort(TARGET_INDEX size, TARGET_TYPE arr[size])
// Sorts an array arr[1..n] into ascending numerical order, by straight insertion. n is input; arr
// is replaced on output by its sorted rearrangement.
{
	TARGET_INDEX i,j;
	TARGET_TYPE a;

	for(j = 1;
		j < size;
		j++)
		{
			a = arr[j];
			i = j-1;

			while(i >= 0 &&
				  arr[i] > a)
			{
				arr[i+1] = arr[i];
				i--;
			}

		arr[i+1] = a;
	}
	// Pick out each element in turn.
	// Look for the place to insert it.
	// Insert it.
}

void main()
{	
	straight_sort(size, arr);
}