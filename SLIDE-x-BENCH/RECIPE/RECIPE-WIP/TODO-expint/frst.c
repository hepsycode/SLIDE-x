#include <stdint.h>
#include <values.h>

typedef long TARGET_TYPE;
typedef uint8_t TARGET_INDEX;

// void expint(TARGET_INDEX n, TARGET_TYPE x);

TARGET_TYPE foo(TARGET_TYPE x)
{
  return x*x+(8*x)<<4-x;
}


/* Function with same flow, different data types,
   nonsensical calculations */
void expint(TARGET_INDEX n, TARGET_TYPE x)
{
  TARGET_INDEX      i,ii,nm1;
  TARGET_TYPE a,b,c,d,del,fact,h,psi,ans;

  nm1=n-1;                      /* arg=50 --> 49 */

  if(x>1)                       /* take this leg? */
    {
      b=x+n;
      c=2e6;
      d=3e7;
      h=d;

      for (i=1;i<=100;i++)      /* MAXIT is 100 */
        {
          a = -i*(nm1+i);
          b += 2;
          d=10*(a*d+b);
          c=b+a/c;
          del=c*d;
          h *= del;
          if (del < 10000)
            {
              ans=h*-x;
              // return ans;
              // return 0;
            }
        }
    }
  else                          /* or this leg? */
    {
      // For the current argument, will always take
      // '2' path here:
      ans = nm1 != 0 ? 2 : 1000;
      fact=1;
      for (i=1;i<=100;i++)      /* MAXIT */
        {
          fact *= -x/i;
          if (i != nm1)         /* depends on parameter n */
            del = -fact/(i-nm1);
          else                  /* this fat piece only runs ONCE */
            {                   /* runs on iter 49 */
              psi = 0x00FF;
              for (ii=1;ii<=nm1;ii++) /*  */
                psi += ii + nm1;
              del=psi+fact* (x*x+(8*x)<<4-x); // foo(x);
            }
          ans += del;
          /* conditional leave removed */
        }

    }
    //return ans;
    // return 0;
}


void main()
{
	expint(50, x);
	
	// with  expint(50,21) as argument, runs the short path
	// in expint.   expint(50,1)  gives the longest execution time

}