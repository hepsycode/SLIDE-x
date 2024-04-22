/* 
 * This is the implementation of sorting algorithm QuickSort:
 * Input:  Monodimensional array of integers 
 * Output: Monodimensional array of sorted integers 
 * Characteristics: In place, uses static memory allocation
 */

#include <stdint.h>
#include <values.h>

typedef int8_t TARGET_TYPE;
typedef int8_t TARGET_INDEX;

//void prototype(int8_t size, float a[size]);

/* As suggested by the name, this function changes the position of two elements which are at position index_1 and index_2 */ 
void swap(TARGET_INDEX index_1, TARGET_INDEX index_2)
{

	TARGET_TYPE b = a[index_1];
	a[index_1] = a[index_2];
	a[index_2] = b;
}


/* 
 * This is the core function of QuickSort, it initializes two pointers (inf and sup) and moves them to an element that is > pivot
 * (in case of inf), <= pivot (in case of sup). At the end, exchanges the elements indicated by pointers.
 * It returns the position of pivot after partition procedure.
 */

TARGET_TYPE partition(TARGET_INDEX init, TARGET_INDEX end)
{
	TARGET_TYPE pivot = a[init];
	TARGET_INDEX sup = end;
	TARGET_INDEX inf = init;

	while(1)
	{
		while(inf <= end && a[inf] <= pivot)
			++inf;

		while(a[sup] > pivot)
			--sup;

		//printf("%d, %d", inf, sup);
		if(inf < sup+1)
			swap(inf, sup);
		else
			break;

	}

	swap(init, sup);
	return sup;

}


/* 
 * The recursive behaviour of quicksort is implemented through a stack. In each frame are stored 
 * the initial index and the final index of the array. This serves to call partition on subarrays.
 */

void quicksort(TARGET_INDEX size, TARGET_TYPE a[size])
{
	TARGET_TYPE stack[size][2];
	TARGET_INDEX stack_size = -1;

	/* This pointer always indicates the head of the stack */
	TARGET_TYPE *top = stack[0];

	TARGET_TYPE pivot_position = 0;
	TARGET_TYPE base = 0;

	stack[++stack_size][0] = size;
	stack[stack_size][1] = a[size];

	while(stack_size >= 0)
	{
		if(top[0] < top[1])
		{	
			pivot_position = partition(top[0], top[1]);
			
			base  = top[0];

			stack[stack_size][0] = pivot_position+1;
			//stack[size][1] = top[1];
			++stack_size;
			stack[stack_size][0] = base;
			stack[stack_size][1] = pivot_position-1;

		}else{

			stack_size--;
		}


		top = stack[stack_size];
	}
}


void main()
{
 	quicksort(size, a);
}
