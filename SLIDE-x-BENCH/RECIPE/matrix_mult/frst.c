#include <stdint.h>
#include <values.h>

typedef double TARGET_TYPE;
typedef uint8_t TARGET_INDEX;

TARGET_TYPE res[size][size];
TARGET_INDEX i, j, k; 
TARGET_TYPE tot = 0;

void matrix_mul()
{
	/* 
	 * If the number of columns of A is different from the b's rows number then 
	 * the multiplication can't be done 
	 */
	 
	/* Iterates through the rows of A */
	for(i = 0; i < size; i++)
	{
		/* Iterates through the columns of B */
		for(k = 0; k < size; k++)
		{
			/* 
			 * Iterates through the columns of A. We need of the "tot" variable to remember 
			 * the value of an element in res array
			 */

			for(tot = 0, j = 0; j < size; j++)
				tot += (a[i][j] * b[j][k]);

			res[i][k] = tot;
		}
	}
}

void main()
{
	matrix_mul();
}
