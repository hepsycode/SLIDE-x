#include <stdint.h>
#include <values.h>

typedef int16_t TARGET_TYPE;
typedef uint16_t TARGET_INDEX;

// A utility function to swap two elements
void swap(TARGET_TYPE arr[size], TARGET_INDEX index_one, TARGET_INDEX index_two){
	TARGET_TYPE temp = arr[index_one];
	arr[index_one] = arr[index_two];
	arr[index_two] = temp;
}

/* This function takes last element as pivot, places the pivot element at its correct position in sorted 
	array, and places all smaller (smaller than pivot) to left of pivot and all greater elements to right 
    of pivot 
*/
TARGET_INDEX partition(TARGET_TYPE arr[size], TARGET_INDEX low, TARGET_INDEX high)
{
	TARGET_INDEX i; //counter
	TARGET_INDEX pivot = high; //the pivot element
	TARGET_INDEX divider_position = low; //the division belt between the low and the high

	//iterate from the starting index and upto (but not including) the pivot
	for(i = low; i < high; i++){
		//if the value is less than the pivot value, shift the element to behind the wall
		if(arr[i] < arr[pivot]){
			swap(arr,divider_position,i);
			//increment the position of the divider
			divider_position++;
		}
	}
	//put the pivot right where The Division Bell lies (gedit?)
	swap(arr,pivot,divider_position);
	//return the index of the divider for subsequent calls to quicksort
	return divider_position;
}

void quicksort_0(TARGET_INDEX low, TARGET_INDEX high)
{
	if(high > low){
		int partition_index = partition(a,low,high);
		quicksort_0(low,partition_index-1);
		quicksort_0(partition_index+1,high);
	}
}

void quicksort()
{
	quicksort_0(0, size-1);
}

void main()
{
	quicksort();
}