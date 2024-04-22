#include <stdint.h>
#include <values.h>

typedef double TARGET_TYPE;
typedef uint64_t TARGET_INDEX;

// Defines

TARGET_TYPE tmp[n][n];

// Functions

/* Main computational kernel. The whole function will be timed,
   including the call and return. */
void kernel2mmFixed()
{
  TARGET_INDEX i, j, k;

  /* D := alpha*A*B*C + beta*D */
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      {
	tmp[i][j] = 0;
	for (k = 0; k < n; ++k)
	  tmp[i][j] += alpha * a[i][k] * b[k][j];
      }
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      {
	d[i][j] *= beta;
	for (k = 0; k < n; ++k)
	  d[i][j] += tmp[i][k] * c[k][j];
      }

}

void main()
{
	kernel2mmFixed();
}
