#include <stdint.h>
#include <values.h>
#include <8051.h>

typedef float TARGET_TYPE;
typedef uint32_t TARGET_INDEX;

void reset_values()
{
    P0 = 0;
    P1 = 0;
    P2 = 0;
    P3 = 0;
}

TARGET_TYPE divide(TARGET_TYPE nu, TARGET_TYPE de) {

    TARGET_TYPE temp = 1;
    TARGET_TYPE quotient = 0;

    while (de <= nu) 
    {
        de <<= 1;
        temp <<= 1;
    }

    //printf("%d %d\n",de,temp,nu);
    while (temp > 1) {
        de >>= 1;
        temp >>= 1;

        if (nu >= de)
		{
            nu -= de;
            //printf("%d %d\n",quotient,temp);
            quotient += temp;
        }
    }

    return quotient;
}

TARGET_TYPE binary_search(TARGET_INDEX n, TARGET_TYPE arr[n], TARGET_TYPE key)
{
	TARGET_TYPE l = 0;
	TARGET_TYPE r = n-1;

	while (l <= r)
	{
		// TARGET_INDEX m = l + (r-l)/2;
		TARGET_INDEX m = l + divide((r-l),2);

		if (arr[m] == key) 
			return m;  

		if (arr[m] < key) 
			l = m + 1; 
		else
			r = m - 1; 
	}

	return -1; 
}

void main()
{
	binary_search(n, arr, key);
    reset_values();
}
