#include <stdint.h>
#include <values.h>

typedef double TARGET_TYPE;
typedef uint64_t TARGET_INDEX;


TARGET_TYPE need[size][size];

//TARGET_TYPE size;

TARGET_INDEX i = 0;
TARGET_INDEX j = 0;

TARGET_TYPE found = 0;

void create_needs()
{
	for(i = 0; i < size; i++)
	{
		for(j = 0; j < size; j++)
			need[i][j] = max[i][j] - allocated[i][j];
	}

}

TARGET_TYPE banker_algorithm()
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
				available[j]  += allocated[i][j];
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
	banker_algorithm();
}
