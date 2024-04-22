#include <stdint.h>
#include <values.h>

typedef int8_t TARGET_TYPE;
typedef uint8_t TARGET_INDEX;

void swap(TARGET_INDEX index_1, TARGET_INDEX index_2)
{

	TARGET_TYPE b = a[index_1];
	a[index_1] = a[index_2];
	a[index_2] = b;
}


TARGET_INDEX partition(TARGET_INDEX low, TARGET_INDEX high)
{
	TARGET_INDEX idx = low - 1;
	TARGET_INDEX j;

	for(j = low; j <= high-1; j++)
	{
		if(a[j] < a[high])
		{
			idx++;
			swap(idx, j);
		}
	}

	swap(idx+1, high);
	return idx+1;
}

void quicksort_0(TARGET_INDEX low, TARGET_INDEX high)
{
	enum{ssize = 130};
	TARGET_INDEX stack[ssize];

	TARGET_INDEX top = -1;
	TARGET_INDEX p;

	stack[++top] = low;
	stack[++top] = high;

	while(top >= 0)
	{
		high = stack[top--];
		low = stack[top--];

		p = partition(low, high);

		if(p - 1 > low)
		{
			stack[++top] = low;
			stack[++top] = p -1;
		}

		if(p + 1 < high)
		{
			stack[++top] = p + 1;
			stack[++top] = high;
		}

	}
}

void quicksort(TARGET_INDEX size, TARGET_TYPE a[size])
{
	quicksort_0(0, size-1);
}

void main()
{
	quicksort(size, a);
}