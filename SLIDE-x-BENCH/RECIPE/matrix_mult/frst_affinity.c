#include <stdint.h>
#include <values.h>

typedef double TARGET_TYPE;
typedef uint8_t TARGET_INDEX;

TARGET_TYPE res[size][size];	
TARGET_INDEX f;
TARGET_INDEX i;
TARGET_INDEX k;

void matrix_mul()
{
	/* 
	 * If the number of columns of A is different from the b's rows number then 
	 * the multiplication can't be done 
	 */
	
	TARGET_TYPE *p_a = (TARGET_TYPE *)&a[0];
	TARGET_TYPE *p_b = (TARGET_TYPE *)&b[0];
	TARGET_TYPE *p_c = (TARGET_TYPE *)&res[0];
	
	/* Iterates through the rows of A */
	for (k = 0 ; k < size ; k++)
	{
		p_a = (TARGET_TYPE *)&a[0]; /* point to the beginning of array A */
		
		/* Iterates through the columns of B */
		for (i = 0 ; i < size; i++)
		{
			p_b = (TARGET_TYPE *)&b[k*size]; /* take next column */
			*p_c = 0;
			for (f = 0 ; f < size; f++) /* do multiply */
			*p_c += *p_a++ * *p_b++;
			*p_c++;
		}
	}
}

int main(void)
{
	matrix_mul();
	return 0;
}
