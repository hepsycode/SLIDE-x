#include <stdint.h>
#include <values.h>
#include <stdio.h>

typedef double TARGET_TYPE;
typedef uint8_t TARGET_INDEX;

//void prototype(int8_t size, int8_t a[size][size], int8_t goal);

TARGET_TYPE frontier[size];
TARGET_TYPE frontier_size = 0;

TARGET_INDEX came_from[size];
TARGET_INDEX current = 0;

TARGET_TYPE priority = 0;
TARGET_INDEX i;
TARGET_INDEX j;

void init_camefrom()
{
	for(i = 0;
		i < size;
		i++)
		came_from[i] = -1;
}

void insert(TARGET_INDEX node, TARGET_TYPE priority)
{
	frontier[node] = priority;
	++frontier_size;
}

void remove_min()
{
	TARGET_TYPE min = 127;

	for(i  = 0;
		i < size;
		i++)
	{
		if(frontier[i] <= min &&
			frontier[i] != 0)
		{
			min = frontier[i];
			current = i;
		}
	}

	--frontier_size;
	frontier[current] = 0;
}

void set_estimates()
{
	for(i = 0;
		i < size;
		i++)
	{
		if(i == 0)
			a[0][0] = 0;
		else
			a[i][i] = 127;
	}
}

TARGET_TYPE absolute(TARGET_TYPE n)
{
	return n > 0 ? n : -n;
}

TARGET_TYPE heuristic(TARGET_INDEX goal, TARGET_INDEX current, TARGET_TYPE path_cost)
{

	if(a[current][goal] > -1)
		return 1;

	/* Taxicab geometry */
	/* Note: we applied to zero, a cast to int8 type */
	return absolute((int8_t)0 - (size/2)) + absolute(path_cost - (size/2));
}

void astarF(TARGET_TYPE a[size][size])
{
	set_estimates();
	init_camefrom();
	insert(0,0);
	TARGET_TYPE tmp1 = 0;

	while(frontier_size > 0)
	{
		remove_min();

		if(current == goal)
			break;

		for(i = 0;
			i < size;
			i++)
		{
			if(a[current][i] != -1 &&   //
				a[current][current] + a[current][i] < a[i][i])
			{
				a[i][i] = a[current][current] + a[current][i];
				priority = a[i][i] + heuristic(goal, i, a[i][i]);
				insert(i, priority);
				came_from[i] = current;
			}

		}
	}
}

void astar()
{
	for(i = 0;
		i < size;
		i++)
	{
		a[i][i] = -1;

		/* Makes the last node the goal node */
		a[size-1][i] = -1;

		for(j = 0;
			j < size;
			j++)
		{
			if(a[i][j] < 0
				&& i != j
				&& a[i][j] != -1 )
			{
				a[i][j] *= -1;
				a[j][i] = -1;
			}
			else
			{

				if(a[j][i] >= 0)
					a[i][j] = -1;
			}
		}
	}
	astarF(a);
}

void main()
{
	astar();
}
