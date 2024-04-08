#include <stdint.h>
#include <stdio.h>
#include <values.h>

typedef int8_t TARGET_TYPE;
typedef int8_t TARGET_INDEX;

void insertionsort()
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
    insertionsort();
}