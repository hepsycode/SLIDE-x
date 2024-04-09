/* bsort100.c */

#include <stdint.h>
#include <8051.h>
#include <values.h>

typedef int64_t TARGET_TYPE;
typedef uint8_t TARGET_INDEX;

//void prototype(int8_t n, int8_t arr[n], int8_t key);

void resetValues()
{
	P0 = 0;
	P1 = 0;
	P2 = 0;
	P3 = 0;
}

/* BUBBLESORT BENCHMARK PROGRAM:
 * This program tests the basic loop constructs, integer comparisons,
 * and simple array handling of compilers by sorting 10 arrays of
 * randomly generated integers.
 */

void bs()
{
/*
 * Sorts an array of integers of size in ascending order.
 */
TARGET_TYPE y[n];
TARGET_INDEX i;

int fvalue, mid, up, low;
  
  y[0] = 0;
  for (i = 1; i < n; i++)
    y[i] = y[i] + 1;

  low = 0;
  up = n-1;
  fvalue = -1 /* all data are positive */ ;
  while (low <= up) {
    mid = (low + up) >> 1;
    if ( y[mid] == key ) {  /*  found  */
      up = low - 1;
      fvalue = arr[mid];
    }
    else  /* not found */
      if ( y[mid] > key ) 	{
	up = mid - 1;
      }
      else   {
             	low = mid + 1;
      }
  }
}


void main()
{
	bs();
	resetValues();
}