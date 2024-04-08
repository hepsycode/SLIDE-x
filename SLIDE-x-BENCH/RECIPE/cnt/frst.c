/* $Id: cnt.c,v 1.3 2005/04/04 11:34:58 csg Exp $ */

/* sumcntmatrix.c */

#include <stdint.h>
#include <values.h>

typedef float TARGET_TYPE;
typedef uint8_t TARGET_INDEX;

//void prototype(int8_t size, int8_t a[size][size]);

  TARGET_TYPE Postotal, Negtotal;
  TARGET_INDEX Poscnt, Negcnt;  
  TARGET_INDEX Outer, Inner;

  TARGET_TYPE Ptotal = 0; /* changed these to locals in order to drive worst case */
  TARGET_TYPE Ntotal = 0;
  TARGET_INDEX Pcnt = 0;
  TARGET_INDEX Ncnt = 0;

void cnt()
{
  
   //InitSeed();
   //printf("\n   *** MATRIX SUM AND COUNT BENCHMARK TEST ***\n\n");
   //printf("RESULTS OF THE TEST:\n");

  for (Outer = 0; Outer < size; Outer++){
    for (Inner = 0; Inner < size; Inner++){
	if (a[Outer][Inner] >= 0) {
	  Ptotal += a[Outer][Inner];
	  Pcnt++;
	}
	else {
	  Ntotal += a[Outer][Inner];
	  Ncnt++;
        }
     }
  }

  Postotal = Ptotal;
  Poscnt = Pcnt;
  Negtotal = Ntotal;
  Negcnt = Ncnt;
}

void main()
{
	cnt();
}