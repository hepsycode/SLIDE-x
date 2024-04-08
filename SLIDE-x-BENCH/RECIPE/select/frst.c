// This functions has been taken from "Numerical Recipes in C" book, Cap 8.5, pag 342
#include <stdint.h>
#include <values.h>

typedef double TARGET_TYPE;
typedef uint8_t TARGET_INDEX;

	TARGET_INDEX i,ir,j,l,mid;
	TARGET_TYPE a,temp;

#define SWAP(a,b) temp=(a);(a)=(b);(b)=temp;

TARGET_TYPE select(TARGET_INDEX k, TARGET_INDEX size, TARGET_TYPE arr[size])
/*
Returns the k th smallest value in the array arr[1..n] . The input array will be rearranged
to have this value in location arr[k] , with all smaller elements moved to arr[1..k-1] (in
arbitrary order) and all larger elements in arr[k+1..n] (also in arbitrary order).
*/
{
	l = 0;	
	ir = size-1;

	for(;;)
	{
		if(ir <= l+1)
		{
			// Active partition contains 1 or 2 elements.
			if (ir == l+1 && arr[ir] < arr[l])
			{
				//Case of 2 elements.
				SWAP(arr[l],arr[ir])
			}
			return arr[k];

		} else {

			mid=(l+ir) >> 1;

			SWAP(arr[mid],arr[l+1])

			if(arr[l] > arr[ir])
			{
				SWAP(arr[l],arr[ir])
			}

			if(arr[l+1] > arr[ir])
			{
				SWAP(arr[l+1],arr[ir])
			}

			if(arr[l] > arr[l+1])
			{
				SWAP(arr[l],arr[l+1])
			}

			i = l+1;
			j = ir;
			a = arr[l+1];

			for(;;) {

				do 
					i++;
				while (arr[i] < a);

				do 
					j--;
				while (arr[j] > a);
				
				if(j < i)
					break;

				SWAP(arr[i],arr[j])
			}

			arr[l+1]=arr[j];
			arr[j]=a;

			if(j >= k)
				ir = j-1;
			if(j <= k)
				l = i;
		}
	}
}

void main()
{
  select(k, size, arr);
}

