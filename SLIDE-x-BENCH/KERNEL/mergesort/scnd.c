#include <stdint.h>
#include <8051.h>
#include <values.h>

typedef int8_t TARGET_TYPE;
typedef int8_t TARGET_INDEX;

void reset_values()
{
	P0 = 0;
	P1 = 0;
	P2 = 0;
	P3 = 0;
}

void merge(TARGET_INDEX left, TARGET_INDEX right, TARGET_INDEX middle)
{
	// Indexes
	TARGET_INDEX i, j, k = 0;
	TARGET_INDEX i1 = middle - left + 1;
	TARGET_INDEX i2 = right - middle;

	// Temporary Arrays
	TARGET_TYPE x[size], y[size] = {0};

	// Copy elements in the temporary arrays x, y
	for(i = 0; i < i1; i++)
		x[i] = a[left + i];

	for(i = 0; i < i2; i++)
		y[i] = a[middle + 1 + i];
	
	i = 0;
	j = 0;
	k = left;
	while(i < i1 && j < i2)
	{		
		if(x[i] <= y[j])
			a[k] = x[i++];
		else
			a[k] = y[j++];

		k += 1;
	}
	
	while(i < i1)
	{
		a[k] = x[i];
		i++;
		k++;
	}
	
	while(j < i2)
	{
		a[k] = y[j];
		j++;
		k++;
	}
}

void mergesort_0(TARGET_INDEX left, TARGET_INDEX right)
{
	if(left < right)
	{
		TARGET_INDEX middle = left+(right-left)/2;

		mergesort_0(left, middle);
		mergesort_0(middle+1, right);

		merge(left, right, middle);
	}
}

void mergesort(TARGET_INDEX size, TARGET_TYPE a[size])
{
	mergesort_0(0, size-1);
}

void main()
{
	mergesort(size, a);
	reset_values();
}
