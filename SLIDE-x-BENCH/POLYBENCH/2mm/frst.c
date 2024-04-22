#include <stdint.h>
#include <values.h>

typedef double TARGET_TYPE;
typedef uint8_t TARGET_INDEX;

// Defines

TARGET_TYPE tmp[ni][nj];

// Functions

/* Main computational kernel. The whole function will be timed,
   including the call and return. */
static void kernel_2mm()
{
  TARGET_INDEX i, j, k;

  /* D := alpha*A*B*C + beta*D */
  for (i = 0; i < ni; i++)
    for (j = 0; j < nj; j++)
      {
	tmp[i][j] = 0;
	for (k = 0; k < nk; ++k)
	  tmp[i][j] += alpha * A[i][k] * B[k][j];
      }
  for (i = 0; i < ni; i++)
    for (j = 0; j < nl; j++)
      {
	D[i][j] *= beta;
	for (k = 0; k < nj; ++k)
	  D[i][j] += tmp[i][k] * C[k][j];
      }

}


void main()
{
	kernel_2mm();
}
