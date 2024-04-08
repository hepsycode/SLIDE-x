#include <stdint.h>
#include <stdio.h>
#include <values.h>

typedef double TARGET_TYPE;
typedef uint8_t TARGET_INDEX;

void insertionsort(TARGET_INDEX size, TARGET_TYPE a[size])
{
    TARGET_INDEX i = 0;
    TARGET_TYPE temp;
    int j = 0;

    for(i = 1; i < size; i++)
    {

        temp = a[i];
        j = i-1;

        while(j >= 0 && temp < a[j])
        {
            a[j+1] = a[j];
            j = j-1;
        }

        a[j+1] = temp;
    }
}

void main()
{
    insertionsort(size, a);
}