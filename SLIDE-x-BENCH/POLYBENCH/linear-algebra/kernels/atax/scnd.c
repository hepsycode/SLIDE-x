#include <stdint.h>
#include <8051.h>
#include <values.h>

typedef int8_t TARGET_TYPE;
typedef int8_t TARGET_INDEX;

//void prototype(int8_t size, int8_t A[size][size], int8_t x[size]);

TARGET_INDEX i;
TARGET_INDEX j;

TARGET_TYPE tmp[size];
TARGET_TYPE y[size];

void resetValues()
{
	P0 = 0;
	P1 = 0;
	P2 = 0;
	P3 = 0;
}

void kernel_atax()
{
  for (i = 0; i < size; i++)
    y[i] = 0;
  for (i = 0; i < size; i++)
    {
      tmp[i] = 0;
      for (j = 0; j < size; j++)
	tmp[i] = tmp[i] + A[i][j] * x[j];
      for (j = 0; j < size; j++)
	y[j] = y[j] + A[i][j] * tmp[i];
    }
}

void main()
{
	kernel_atax();
	resetValues();
}