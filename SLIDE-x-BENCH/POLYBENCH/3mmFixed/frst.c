#include <stdint.h>
#include <values.h>

typedef double TARGET_TYPE;
typedef uint64_t TARGET_INDEX;

// Defines
TARGET_TYPE e[size][size];
TARGET_TYPE f[size][size];
TARGET_TYPE g[size][size];

// Functions

/* Main computational kernel. The whole function will be timed,
   including the call and return. */
void kernel_3mm_fixed()
{
  TARGET_INDEX i, j, k;

  /* E := A*B */
  for (i = 0; i < size; i++)
    for (j = 0; j < size; j++)
      {
	e[i][j] = 0;
	for (k = 0; k < size; ++k)
	  e[i][j] += a[i][k] * b[k][j];
      }
  /* F := C*D */
  for (i = 0; i < size; i++)
    for (j = 0; j < size; j++)
      {
	f[i][j] = 0;
	for (k = 0; k < size; ++k)
	  f[i][j] += c[i][k] * d[k][j];
      }
  /* G := E*F */
  for (i = 0; i < size; i++)
    for (j = 0; j < size; j++)
      {
	g[i][j] = 0;
	for (k = 0; k < size; ++k)
	  g[i][j] += e[i][k] * f[k][j];
      }
}


void main()
{
	kernel_3mm_fixed();
}
