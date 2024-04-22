#include <stdint.h>
#include <values.h>

typedef double TARGET_TYPE;
typedef uint64_t TARGET_INDEX;

// Defines

// Functions

/* Main computational kernel. The whole function will be timed,
   including the call and return. */
void kernel_adi()
{	
  TARGET_INDEX t, i1, i2;

  for (t = 0; t < tsteps; t++)
    {
      for (i1 = 0; i1 < n; i1++)
	for (i2 = 1; i2 < n; i2++)
	  {
	    x[i1][i2] = x[i1][i2] - x[i1][i2-1] * a[i1][i2] / b[i1][i2-1];
	    b[i1][i2] = b[i1][i2] - a[i1][i2] * a[i1][i2] / b[i1][i2-1];
	  }

      for (i1 = 0; i1 < n; i1++)
	x[i1][n-1] = x[i1][n-1] / b[i1][n-1];

      for (i1 = 0; i1 < n; i1++)
	for (i2 = 0; i2 < n-2; i2++)
	  x[i1][n-i2-2] = (x[i1][n-2-i2] - x[i1][n-2-i2-1] * a[i1][n-i2-3]) / b[i1][n-3-i2];

      for (i1 = 1; i1 < n; i1++)
	for (i2 = 0; i2 < n; i2++) {
	  x[i1][i2] = x[i1][i2] - x[i1-1][i2] * a[i1][i2] / b[i1-1][i2];
	  b[i1][i2] = b[i1][i2] - a[i1][i2] * a[i1][i2] / b[i1-1][i2];
	}

      for (i2 = 0; i2 < n; i2++)
	x[n-1][i2] = x[n-1][i2] / b[n-1][i2];

      for (i1 = 0; i1 < n-2; i1++)
	for (i2 = 0; i2 < n; i2++)
	  x[n-2-i1][i2] = (x[n-2-i1][i2] - x[n-i1-3][i2] * a[n-3-i1][i2]) / b[n-2-i1][i2];
    }
}


void main()
{
	kernel_adi();
}
