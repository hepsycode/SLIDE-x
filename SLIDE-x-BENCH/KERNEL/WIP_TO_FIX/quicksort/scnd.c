#include <stdint.h>
#include <8051.h>
#include <values.h>

typedef float TARGET_TYPE;
typedef long TARGET_INDEX;

/*
 * Swaps two elements of 'a';
 * @param i: index of the source element;
 * @param j: index of the target element;
 */
void swap(TARGET_INDEX i, TARGET_INDEX j)
{
	TARGET_TYPE source = a[i];
	TARGET_TYPE target = a[j];
	a[i] = target;
	a[j] = source;
}

TARGET_TYPE partition(TARGET_INDEX lower, TARGET_INDEX upper)
{
	TARGET_INDEX i, j = 0;
	
	TARGET_TYPE pivot = a[upper];
	i = lower-1;

	for(j = lower; j <= upper-1; j++)
	{
		if(a[j] <= pivot)
		{

			i += 1;
			swap(i, j);
		}
	}

	swap(i+1, upper);
	return (i+1);
}

#ifndef STACK
#define STACK
TARGET_INDEX stack[size];
#endif
void quicksort(TARGET_INDEX size, TARGET_TYPE a[size])
{
	// TARGET_INDEX stack[size];
	TARGET_INDEX top = -1;
	TARGET_INDEX start = 0;
	TARGET_INDEX end = size-1;

	// push
	stack[++top] = start;
	stack[++top] = end;
	
	while(top >= 0)
	{

		// pop
		end = stack[top--];
		start = stack[top--];
	
		TARGET_INDEX partition_index = partition(start, end);
				
		if(partition_index - 1 > start)
		{

			stack[++top] = start;
			stack[++top] = partition_index - 1;
		}

		if(partition_index + 1 < end)
		{
			stack[++top] = partition_index + 1;
			stack[++top] = end;
		}
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
	quicksort(size, a);
	reset_values();
}
