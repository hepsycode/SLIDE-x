#include <stdint.h>
#include <8051.h>
#include <values.h>

typedef float TARGET_TYPE;
typedef unsigned long TARGET_INDEX;

unsigned int bitrev(TARGET_TYPE n)
{
	unsigned int NO_OF_BITS = sizeof(n) * 8; 
	unsigned int reverse_num = 0, i, temp; 
  
	for (i = 0; i < NO_OF_BITS; i++) 
	{ 
		temp = (n & (1 << i)); 
		if(temp) 
		    reverse_num |= (1 << ((NO_OF_BITS - 1) - i)); 
	} 

	return reverse_num; 

}

void reset_values()
{
	P0 = 0;
	P1 = 0;
	P2 = 0;
	P3 = 0;
}

void main()
{
	bitrev(n);
	reset_values();
}