/* $Id: duff.c,v 1.2 2005/04/04 11:34:58 csg Exp $ */

/*----------------------------------------------------------------------
 *  WCET Benchmark created by Jakob Engblom, Uppsala university,
 *  February 2000.
 *
 *  The purpose of this benchmark is to force the compiler to emit an
 *  unstructured loop, which is usually problematic for WCET tools to
 *  handle.
 *
 *  The execution time should be constant.
 *
 *  The original code is "Duff's Device", see the Jargon File, e.g. at
 *  http://www.tf.hut.fi/cgi-bin/jargon.  Created in the early 1980s
 *  as a way to express loop unrolling in C.
 *
 *----------------------------------------------------------------------*/

#include <stdint.h>
#include <8051.h>
#include <values.h>

typedef float TARGET_TYPE;
typedef uint8_t TARGET_INDEX;

void resetValues()
{
	P0 = 0;
	P1 = 0;
	P2 = 0;
	P3 = 0;
}

void duff()
{
TARGET_TYPE source[size];

TARGET_INDEX i;
TARGET_INDEX count;
TARGET_INDEX n;

TARGET_TYPE *py;
TARGET_TYPE *px;

  count = 43;  /* exec time depends on this one! */
  n=(count+7)/8;

  for(i=0;i<size;i++)
  {
    source[i] = size-i;
  }
  
  *px = source;
  *py = a;
  
  switch(count%8){
  case 0: do{     *px++ = *py++;
  case 7:         *px++ = *py++;
  case 6:         *px++ = *py++;
  case 5:         *px++ = *py++;
  case 4:         *px++ = *py++;
  case 3:         *px++ = *py++;
  case 2:         *px++ = *py++;
  case 1:         *px++ = *py++;
  } while(--n>0);
  }
}

void main()
{
	duff();
	resetValues();
}

/*------------------------------------------------------------
 * $Id: duff.c,v 1.2 2005/04/04 11:34:58 csg Exp $
 *------------------------------------------------------------
 * $Log: duff.c,v $
 * Revision 1.2  2005/04/04 11:34:58  csg
 * again
 *
 * Revision 1.1  2005/03/29 09:34:13  jgn
 * New file.
 *
 * Revision 1.8  2000/10/16 07:48:15  jakob
 * *** empty log message ***
 *
 * Revision 1.7  2000/05/22 11:02:18  jakob
 * Fixed minor errors.
 *
 * Revision 1.6  2000/02/27 16:56:52  jakob
 * *** empty log message ***
 *
 * Revision 1.5  2000/02/15 14:09:24  jakob
 * no message
 *
 * Revision 1.2  2000/02/15 13:32:16  jakob
 * Added duff's device to benchmark suite for LCTES 00 paper.
 *
 *
 *------------------------------------------------------------*/
