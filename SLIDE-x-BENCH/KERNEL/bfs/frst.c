#include <stdint.h>
#include <values.h>

typedef int32_t TARGET_TYPE;
typedef uint32_t TARGET_INDEX;

TARGET_INDEX current, i, tail, head = 0;
TARGET_TYPE visited[size];

void enqueue(TARGET_TYPE par)
{
	if((tail-head) != size-1)
	{
		visited[tail] = par;
		tail = (tail+1) % size;
	}
}

TARGET_TYPE dequeue()
{
	TARGET_TYPE element = 0;

	if(head != tail)
	{	
		element = visited[head];
		head = (head+1) % size;
	}

	return element;
}

void clean_input()
{
	head, tail = 0;

	for(i = 0; i < size; i++) {
		visited[i] = 0;
		a[i][i] = -1;
	}
}

void bfs()
{
	/* 
	 * We store a -1 in a[node][node] position to indicate that a node has been already visited
	 */

	a[0][0] = -2;
	enqueue(0);

	while(head != tail)
	{
		current = dequeue();
		for(i  = 0; i < size; i++)
		{	
			if(a[i][i] != -2 && a[current][i] > 0)	
			{
				enqueue(i);
				a[i][i] =  -2;
			}
		}
	}
}

void main()
{
	// clean_input();
	bfs();
}