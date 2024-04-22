#include <stdint.h>
#include <values.h>

typedef double TARGET_TYPE;
typedef uint64_t TARGET_INDEX;

TARGET_INDEX current, i, tail, head;
TARGET_TYPE visited[size], element;

void clean_input()
{
	head, tail = 0;

	for(i = 0; i < size; i++){
		visited[i] = 0;
		a[i][i] = -1;
	}
}

void dfs()
{	
	head = 0;
	visited[head] = 0;
	++tail;

	while(tail > 0)
	{
		current = visited[head];
		--tail;

		if(a[current][current] != -2)
		{
			a[current][current] = -2;

			for(i = 0;
				i < size;
				i++)
			{
				if(a[i][i] != -2 &&
					a[current][i] > 0)	
				{
					visited[tail++] = i;
					head = tail-1;
				}
			}
			
		}
	}
}

void main()
{
	clean_input();
	dfs();
}