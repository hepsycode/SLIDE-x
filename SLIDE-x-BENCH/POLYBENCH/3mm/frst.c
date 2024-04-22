#include <stdint.h>
#include <values.h>

typedef double TARGET_TYPE;
typedef uint64_t TARGET_INDEX;

// Defines
TARGET_TYPE e[ni][nj];
TARGET_TYPE f[nj][nl];
TARGET_TYPE g[ni][nl];

// Functions

/* Main computational kernel. The whole function will be timed,
   including the call and return. */
static void kernel_3mm()
{
  TARGET_INDEX i, j, k;

  /* E := A*B */
  for (i = 0; i < ni; i++)
    for (j = 0; j < nj; j++)
      {
	e[i][j] = 0;
	for (k = 0; k < nk; ++k)
	  e[i][j] += a[i][k] * b[k][j];
      }
  /* F := C*D */
  for (i = 0; i < nj; i++)
    for (j = 0; j < nl; j++)
      {
	f[i][j] = 0;
	for (k = 0; k < nm; ++k)
	  f[i][j] += c[i][k] * d[k][j];
      }
  /* G := E*F */
  for (i = 0; i < ni; i++)
    for (j = 0; j < nl; j++)
      {
	g[i][j] = 0;
	for (k = 0; k < nj; ++k)
	  g[i][j] += e[i][k] * f[k][j];
      }
}


void main()
{
	kernel_3mm();
}
