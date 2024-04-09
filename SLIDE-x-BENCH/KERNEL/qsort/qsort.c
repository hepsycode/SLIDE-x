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
/*  FILE: qsort-exam.c                                                   */
/*  SOURCE : Numerical Recipes in C - The Second Edition                 */
/*                                                                       */
/*  DESCRIPTION :                                                        */
/*                                                                       */
/*     Non-recursive version of quick sort algorithm.                    */
/*     This example sorts 20 floating point numbers, arr[].              */
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

#define SWAP(a,b) temp=(a);(a)=(b);(b)=temp;
#define M 7

TARGET_TYPE istack[10];

void qsort(TARGET_INDEX n, TARGET_TYPE arr[n])
{
	TARGET_INDEX i, ir = n, j, k, l = 1;

	TARGET_INDEX jstack = 0;

	TARGET_INDEX flag;
	TARGET_TYPE a, temp;

	flag = 0;
	
	for (;;) 
	{
		if (ir-l < M)
		{
			for(j = l+1;
				j <= ir;
				j++)
			{
				a = arr[j];

				for(i = j-1;
					i >= l;
					i--)
				{
					if(arr[i] <= a)
						break;

					arr[i+1] = arr[i];
				}

				arr[i+1] = a;
			}

			if (jstack == 0)
				break;

			ir = istack[jstack--];
			l = istack[jstack--];

		} else
		{
			k = (l+ir) >> 1;
			SWAP(arr[k],arr[l+1])

			if(arr[l] > arr[ir])
			{
				SWAP(arr[l],arr[ir])
			}

			if(arr[l+1] > arr[ir])
			{
				SWAP(arr[l+1],arr[ir])
			}

			if (arr[l] > arr[l+1])
			{
				SWAP(arr[l],arr[l+1])
			}

			i = l+1;
			j = ir;
			a = arr[l+1];
			
			for(;;)
			{
				i++; 
				while(arr[i] < a)
					i++;
				j--;
				while(arr[j] > a)
					j--;

				if(j < i)
					break;
				
				SWAP(arr[i],arr[j]);
			}

			arr[l+1] = arr[j];
			arr[j] = a;
			jstack += 2;

			if(ir - i + 1 >= j-l)
			{
				istack[jstack] = ir;
				istack[jstack-1] = i;
				ir = j-1;
			} else {
				istack[jstack]=j-1;
				istack[jstack-1]=l;
				l=i;
			}
		}
	}
}

void main()
{
	qsort(n, arr);
}

