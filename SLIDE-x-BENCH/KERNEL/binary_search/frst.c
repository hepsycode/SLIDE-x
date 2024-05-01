#include <stdint.h>
#include <values.h>

typedef int64_t TARGET_TYPE;
typedef uint64_t TARGET_INDEX;

//void prototype(int8_t n, int8_t arr[n], int8_t key);

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

TARGET_TYPE binary_search()
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
	binary_search();
}
