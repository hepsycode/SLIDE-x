#include <stdint.h>
#include <8051.h>
#include <values.h>

typedef int8_t TARGET_TYPE;
typedef int8_t TARGET_INDEX;

TARGET_TYPE dist[size];

void dijkstra(TARGET_INDEX size , TARGET_TYPE a[size][size])
{
	TARGET_INDEX i, j, up, val, min = 0;
	TARGET_TYPE new_dist;
	 
	// Calculates the maximum value for the current datatype
	up = 1;
	for(i = 0; i < (8*sizeof(TARGET_TYPE)) - 1; i++)
		up *= 2;
	up -= 1;

	// Makes the graph simmetric and without self-loops
	for(i = 0; i < size; i++)
	{
		for(j = 0; j < size; j++)
		{
			// Removes negative values
			if(a[i][j] < 0)
				a[i][j] *= -1;
			// Removes self-loops
			if(i == j)
				a[i][j] = 0;
			// Makes the graph simmetric
			if(a[i][j] != a[j][i])
				a[j][i] = a[i][j]; 
		}
	}
	
	// Initializes the distances array
	for(i = 0; i < size; i++)
		dist[i] = up;
	
	// Sets the source equal to zero
	dist[0] = 0;

	while(1)
	{
		// Checks if vset is empty prev: vset[i] == 1
		for(i = 0; a[i][i] == -1; i++);

		// If yes ends the execution
		if(i == size) 
			return;

		// Takes the node in vset with the smallest dist
		val = up;
		for(i = 0; i < size; i++)
		{
			// If the node has not been visited vset[i] = 1
			if(a[i][i] == 0)
			{
				if(dist[i] < val)
				{
					val = dist[i];
					min = i;
				}
			}
		}

		// Removes min from the vertex set prev vset[min] = 1
		a[min][min] = -1;
	
		// Iterates through the neighbors of min
		for(j = 0; j < size; j++)
		{
			if(min != j)
			{
				new_dist = dist[min] + a[min][j];
				
				// Relax (min, j)
				if(new_dist < dist[j])
					dist[j] = new_dist;
			}
		}
	}
}

void reset_values()
{
	P0 = 0;
	P1 = 0;
	P2 = 0;
	P3 = 0;
}


void main()
{
	dijkstra(size, a);
	reset_values();
}	
