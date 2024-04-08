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
/*  FILE: fft1.c                                                         */
/*  SOURCE : Turbo C Programming for Engineering by Hyun Soon Ahn        */
/*                                                                       */
/*  DESCRIPTION :                                                        */
/*                                                                       */
/*     FFT using Cooly-Turkey algorithm.                                 */
/*     There are two inputs, ar[] and ai[]. ar[] is real number parts    */
/*     of input array and the ai[] is imaginary number parts of input.   */
/*     The function fft1 process FFT or inverse FFT according to the    .*/
/*     parameter flag. (FFT with flag=0, inverse FFT with flag=1).       */
/*                                                                       */
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
typedef uint8_t TARGET_INDEX;

#define SWAP(a,b) tempr=(a);(a)=(b);(b)=tempr
#define PI 3.14159f

TARGET_TYPE is_power_of_two()
{	
	if(nn == 1 || nn == 2 || nn == 4 || nn == 8 || nn == 16 || nn == 32 || nn == 64)
		return 1;

	return 0;
}

void convert_nn()
{
	while(1)
	{
		--nn;
		if(is_power_of_two())
			break;
	}

}

//  SOURCE : Turbo C Programming for Engineering by Hyun Soon Ahn
TARGET_TYPE myabs(TARGET_TYPE n)
{

  TARGET_TYPE f;

  if(n >= 0) 
  	f = n;
  else
  	f = -n;
 
  return f;
}

//  SOURCE : Turbo C Programming for Engineering by Hyun Soon Ahn
TARGET_TYPE mysin(TARGET_TYPE rad)
{
	TARGET_TYPE app;

	TARGET_TYPE diff;
	TARGET_TYPE inc = 1;

	while (rad > 2*PI)
		rad -= 2*PI;
	while (rad < -2*PI)
		rad += 2*PI;

	app = diff = rad;
	
	diff = (diff * (-(rad*rad))) / ((2.0f * inc) * (2.0f * inc + 1.0f));
	app = app + diff;
	inc++;
	
	while(myabs(diff) >= 0.00001f)
	{
		diff = (diff * (-(rad*rad))) / ((2.0f * inc) * (2.0f * inc + 1.0f));
		app = app + diff;
		inc++;
	}

	return(app);
}


void fft(TARGET_TYPE nn, TARGET_INDEX size, TARGET_TYPE data[size], TARGET_INDEX isign)
{
	TARGET_INDEX n,mmax,m,j,istep,i;
	TARGET_TYPE wtemp,wr,wpr,wpi,wi,theta;
	TARGET_TYPE tempr,tempi;
	// Double precision for the trigonomet-ric recurrences.

	n = nn << 1;
	j = 1;
	
	for(i=1;
	    i<n;
	    i+=2)
	{
		//This is the bit-reversal section of the routine
		if(j > i) 
		{
			SWAP(data[j],data[i]);
			//Exchange the two complex numbers.
			SWAP(data[j+1],data[i+1]);
		}
		m = nn;
		while(m >= 2 && j > m)
		{
			j -= m;
			m >>= 1;
		}
		j += m;
	}

	mmax = 2;
	
	while(n > mmax) 
	{
		// Outer loop executed log 2 nn times.
		istep = mmax << 1;
		theta = isign*(6.28318530717959f/mmax);
		// Initialize the trigonometric recurrence.
		wtemp = mysin(0.5f*theta);
		wpr = -2.0f*wtemp*wtemp;

		wpi = mysin(theta);
		wr=1.0f;
		wi=0.0f;

		for(m=1;
		    m<mmax;
		    m+=2)
		{
			for(i=m;
			    i<=n;
			    i+=istep)
			{
				j=i+mmax;
				tempr=wr*data[j]-wi*data[j+1];
				tempi=wr*data[j+1]+wi*data[j];
				data[j]=data[i]-tempr;
				data[j+1]=data[i+1]-tempi;
				data[i] += tempr;
				data[i+1] += tempi;
			}
			wr=(wtemp=wr)*wpr-wi*wpi+wr;
			wi=wi*wpr+wtemp*wpi+wi;
		}
		mmax=istep;

	}
}

void main()
{
  fft(nn, size, data, isign);
}
