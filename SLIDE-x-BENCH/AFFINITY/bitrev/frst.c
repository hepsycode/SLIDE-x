#include <stdint.h>
#include <values.h>

typedef float TARGET_TYPE;
typedef unsigned long TARGET_INDEX;

#define two(x)       (1 << (x))                  /* \(2\sp{x}\) by left-shifting */

/* bitrev.c - bit reverse of a B-bit integer n */

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

void main()
{
	bitrev(n);
}

