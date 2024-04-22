#include <stdint.h>
#if (!defined(_GCOV_EXE_))
#include <8051.h>
#endif
#include <values.h>

typedef int8_t TARGET_TYPE;
typedef uint8_t TARGET_INDEX;

// Defines

// Functions

#if (!defined(_GCOV_EXE_))
void reset_values()
{
	P0 = 0;
	P1 = 0;
	P2 = 0;
	P3 = 0;
}
#endif

void function_name()
{	
	// Computation
}


void main()
{
	function_name();
	#if (!defined(_GCOV_EXE_))
	reset_values();
	#endif
}

