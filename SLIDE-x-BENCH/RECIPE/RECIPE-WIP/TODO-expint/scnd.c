#include <stdint.h>
#include <8051.h>
#include <values.h>

typedef float TARGET_TYPE;
typedef uint8_t TARGET_INDEX;

void resetValues()
{
	P0 = 0;
	P1 = 0;
	P2 = 0;
	P3 = 0;
}

void cnt()
{

}

void main()
{
	cnt();
	resetValues();
}