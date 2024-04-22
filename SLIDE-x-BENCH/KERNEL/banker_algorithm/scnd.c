#include <stdint.h>
#include <8051.h>
#include <values.h>

typedef int8_t TARGET_TYPE;
typedef uint8_t TARGET_INDEX;

#ifndef NEED
#define NEED
TARGET_TYPE need[size][size];
#endif

TARGET_INDEX i = 0;
TARGET_INDEX j = 0;

TARGET_TYPE found = 0;

void resetValues()
{
	P0 = 0;
	P1 = 0;
	P2 = 0;
	P3 = 0;
}

void create_needs()
{
	for(i = 0; i < size; i++)
	{
		for(j = 0; j < size; j++)
			need[i][j] = max[i][j] - allocated[i][j];
	}

}

TARGET_TYPE banker_algorithm(TARGET_INDEX size, TARGET_TYPE available[size], TARGET_TYPE allocated[size][size], TARGET_TYPE max[size][size])
{	
	for(i = 0; i < size; i++)
	{
		
		for(j = 0; j < size; j++)
		{

			available[j] -= need[i][j];
			allocated[i][j] += need[i][j];
			
			found = 0;

			if(need[i][j] <= available[j] /*&&*/ 
				/*need[i][j] >= 0 */ )
			{
				available[j] += allocated[i][j];
				found = 1;
			}

			if(found == 0)
				return -1;
		}

	}

	return 1;
}


void main()
{

	create_needs();
	banker_algorithm(size, available, allocated,max);
	resetValues();
}
