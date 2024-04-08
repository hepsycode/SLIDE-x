/* MDH WCET BENCHMARK SUITE. */

/* 2012/09/28, Jan Gustafsson <jan.gustafsson@mdh.se>
 * Changes:
 *  - This program redefines the C standard function sqrt. Therefore, this function has been renamed to sqrtfcn.
 *  - qrt.c:79:15: warning: explicitly assigning a variable of type 'float' to itself: fixed
 */

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
/*  FILE: sqrt.c                                                         */
/*  SOURCE : Public Domain Code                                          */
/*                                                                       */
/*  DESCRIPTION :                                                        */
/*                                                                       */
/*     Square root function implemented by Taylor series.                */
/*                                                                       */
/*  REMARK :                                                             */
/*                                                                       */
/*  EXECUTION TIME :                                                     */
/*                                                                       */
/*                                                                       */
/*************************************************************************/
#include <stdint.h>
#include <values.h>

typedef float TARGET_TYPE;
typedef int8_t TARGET_INDEX;

TARGET_TYPE myabs(TARGET_TYPE x)
{
   if (x < 0)
      return -x;
   else
      return x;
}

TARGET_TYPE sqrtfnc(TARGET_TYPE val)
{
   TARGET_TYPE x = val/10;

   TARGET_TYPE dx;

   TARGET_TYPE diff;
   TARGET_TYPE min_tol = 0.00001;

   TARGET_INDEX i, flag;

   flag = 0;

   if (val == 0 )
      x = 0;
   else 
   {
      for(i=1;
          i<20;
          i++)
      {
         if (!flag)
         {
            dx = (val - (x*x)) / (2.0 * x);
            x = x + dx;
            diff = val - (x*x);

            if(myabs(diff) <= min_tol)
               flag = 1;
         }
         else {} /* JG */
/*            x =x; */
      }
   }

   return (x);
}

void main()
{
   sqrtfnc(val);
}