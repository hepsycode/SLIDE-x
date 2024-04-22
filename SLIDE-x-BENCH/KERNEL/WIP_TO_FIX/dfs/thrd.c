#include <stdint.h>
#include <values.h>

typedef int8_t TARGET_TYPE;
typedef int8_t TARGET_INDEX;

int8_t current, i, j, tail, head = 0;
TARGET_TYPE visited[size];

TARGET_TYPE resto(int8_t a, TARGET_INDEX b)

{	TARGET_TYPE x;
	while(a>0)
	{
		x=a;
		a=a-b;
	}
    return x;
}

void enqueue(TARGET_TYPE par)
{
	if((tail-head) != size-1)
	{
		visited[tail] = par;
		tail = resto((tail+1),  size);
	}
}

TARGET_TYPE dequeue()
{
	TARGET_TYPE element = 0;

	if(head != tail)
	{	
		element = visited[head];
		head = resto((head+1) , size);
	}

	return element;
}



void bfs()
{
	// We store a -1 in a[node][node] position to indicate that a node has been already visited
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
	bfs();
}
