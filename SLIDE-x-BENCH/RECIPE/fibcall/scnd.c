/* $Id: fibcall.c,v 1.2 2005/04/04 11:34:58 csg Exp $ */

/*************************************************************************/
/*                                                                       */
/*   SNU-RT Benchmark Suite for Worst Case Timing Analysis               */
/*   =====================================================               */
/*                              Collected and Modified by S.-S. Lim      */
/*                                           sslim@archi.snu.ac.kr       */
/*                                         Real-Time Research Group      */
/*                                        Seoul National University      */
/*                                                                       */
/*                                                                       */
/*        < Features > - restrictions for our experimental environment   */
/*                                                                       */
/*          1. Completely structured.                                    */
/*               - There are no unconditional jumps.                     */
/*               - There are no exit from loop bodies.                   */
/*                 (There are no 'break' or 'return' in loop bodies)     */
/*          2. No 'switch' statements.                                   */
/*          3. No 'do..while' statements.                                */
/*          4. Expressions are restricted.                               */
/*               - There are no multiple expressions joined by 'or',     */
/*                'and' operations.                                      */
/*          5. No library calls.                                         */
/*               - All the functions needed are implemented in the       */
/*                 source file.                                          */
/*                                                                       */
/*                                                                       */
/*************************************************************************/
/*                                                                       */
/*  FILE: fibcall.c                                                      */
/*  SOURCE : Public Domain Code                                          */
/*                                                                       */
/*  DESCRIPTION :                                                        */
/*                                                                       */
/*     Summing the Fibonacci series.                                     */
/*                                                                       */
/*  REMARK :                                                             */
/*                                                                       */
/*  EXECUTION TIME :                                                     */
/*                                                                       */
/*                                                                       */
/************************************************************************/

#include <stdint.h>
#if (!defined(_GCOV_EXE_))
#include <8051.h>
#endif
#include <values.h>

typedef long TARGET_TYPE;
typedef uint8_t TARGET_INDEX;

    TARGET_INDEX i;
    TARGET_TYPE Fnew, Fold, temp, ans;

#if (!defined(_GCOV_EXE_))
void reset_values()
{
  P0 = 0;
  P1 = 0;
  P2 = 0;
  P3 = 0;
}
#endif


void fibcall(TARGET_TYPE n)
{
    Fnew = 1; 
    Fold = 0;

    for(i = 2;
	      i <= n;
	      i++)
    {
      temp = Fnew;
      Fnew = Fnew + Fold;
      Fold = temp;
      //printf("Fnew: %d\n", Fnew);
    }

    ans = Fnew;

  //return ans;
}

void main()
{
  fibcall(n);
  #if (!defined(_GCOV_EXE_))
  reset_values();
  #endif
}
