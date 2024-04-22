#include <stdint.h>
#include <8051.h>
#include <values.h>

typedef float TARGET_TYPE;
typedef long TARGET_INDEX;


/* This data structure is used to maintain the disjoint sets */
TARGET_TYPE union_find[size];

/* Indexes used to iterate a bidimensional matrix */
TARGET_INDEX i = 0; 
TARGET_INDEX j = 0;

/* Indexes used in find_min() */
TARGET_INDEX k = 0;
TARGET_INDEX z = 0; 

/* Indexes used to store node_A and node_B of minimum edge cost */
TARGET_INDEX x = 0;
TARGET_INDEX y = 0;

/* Variable useful during find_min() function */
TARGET_TYPE min = 0;

TARGET_TYPE edge_number = 0;

void resetValues()
{
	P0 = 0;
	P1 = 0;
	P2 = 0;
	P3 = 0;
}

/* This function return 1 if the graph is connected else 0 */
TARGET_TYPE is_connected()
{
	for(i = 0; 
		i < size;
		i++)
	{
		for(j = 0;
			j < size;
			j++)
		{
			/* Break if there is at least a connected node */
			if(i != j &&
			   a[i][j] != -1)
				break;
		}

		if(j == size)
			return 0;
	}

	return 1;
}

/* 
 * This function finds the edge with minimum cost
 */
void find_min()
{
	min = 127;

	for(k = 0;
		k < size-1;
		k++)
	{
		for(z = k;
			z < size;
			z++)
		{
			if(a[k][z] <= min && 
				a[k][z] != -1)
			{
				min = a[k][z];

				/* This two assignments saves the nodes of minimum cost edge */
				x = k;
				y = z;
			}
		}
	}

	/* This statement is done to avoid this position in the next call of find_min() */
	a[x][y] = -1;
}

/*
 * The graph is generated casually so we can have an oriented graph.
 * This requirements of the algorithm forces the input to be a non oriented graph
 * This function makes the input graph a non oriented graph. 
 */

void make_non_oriented()
{
	for(i = 0; 
		i < size; 
		i++)
	{
		a[i][i] = -1;

		for(j = 0; 
			j < size; 
			j++)
		{
			/*
			if(a[i][j] >= 0)
				a[j][i] = a[i][j];
			*/

			if(a[i][j] < 0 && 
				i != j)
				a[i][j] *= -1;
				

			a[j][i] = a[i][j];

		}
	}
}

/* 
 * This function initializes the array union_find wich will be used to store
 * disjoints set
 */
void init_union_find()
{
	for(i = 0; 
		i < size; 
		i++)
	{
		union_find[i] = -1;
	}
}

/* This function merge two disjoint sets */
void union_sets()
{	
	z = union_find[y];

	for(k = 0;
		k < size;
		k++)
	{
		if(union_find[k] == z)
			union_find[k] = union_find[x];
	}

}

/* Given a node, this function returns the name of the set in which is cointained */
TARGET_TYPE find(TARGET_INDEX node)
{
	return union_find[node];
}

/* make_set() creates a set only containing a single element */
void make_set(TARGET_INDEX node)
{
	union_find[node] = node;
}

/* Function for debugging  
void print_sets()
{
	int8_t w;
	for(w = 0; 
		w < size; 
		w++)
		printf("%d ", union_find[w]);

	printf("\n");
}
*/
/* This function counts how much edges we have in the graph */
void count_edges()
{
	for(i = 0; 
		i < size; 
		i++)
	{
		for(j = i; 
			j < size; 
			j++)
		{
			if(a[i][j] != -1)
				edge_number++;
		}
	}
}

/* 
 * This is the function that implements the algorithm, at the end we will find the 
 * edges with minimum cost in the double dimension matrix in input
 */

void kruskal(TARGET_INDEX size, TARGET_TYPE a[size][size])
{
	count_edges();

	/* For each vertex in the graph, make_set() */
	for(i = 0; 
		i < size; 
		i++)
		make_set(i);

	/* For each edge in G choosen in non decreasing order */
	for(i = 0;
		i < edge_number;
		i++)
	{
		find_min();

		if(find(x) != find(y))
			union_sets();
		else
		{
			a[x][y] = -1;
			a[y][x] = -1;
		}
	}

}

void main()
{
	make_non_oriented();
	init_union_find();

	/*
	if(is_connected())
		kruskal(size, a);
	*/

	resetValues();
}