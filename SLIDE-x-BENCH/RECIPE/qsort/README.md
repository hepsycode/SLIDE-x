## QuickSort Sorting Algorithm: brief description of the implementation.

This is an implementation "in place" of the algorithm in the sense that the sorting is done without using extra buffer,
all the computation is done on the input array. 
This implementation is an iterative one. It simulates the recursive behavior with a static array.

We have 3 main procedures: quicksort(), partition(), swap().

<b>Swap:</b> Simply exchanges position of two elements in the array.

<b>Partition:</b> Uses two pointers (inf and sup) and moves them to an element that is > pivot (in case of inf), <= pivot (in case of sup). At the end, exchanges the elements indicated by pointers. It returns the position of pivot after partition procedure. This function puts the elements smaller than the pivot to his left and the bigger ones to his right.

<b>QuickSort:</b> This is the main function. In it is defined the stack. In each frame of the stack are stored two indexes: initial and final. These two indexes indicate the initial index and the final one of a piece of the original array. This is done in order to do call partition function on subarrays.

### Test and Implementation Details:
void prototype(int size, int a[size]);<br>

*******************
TARGET_INDEX:<b>int8_t</b>
TARGET_TYPE:<b>int8_t</b>

- 8 + size}a + (size * 2)}stack
- size <= 36 -----> 8 + (36)}a + (36 * 2)}stack -------> TOT: 116

<b> int8_t size:</b>&nbsp;&nbsp;[1, 36]; 100 <br>
<b> int8_t a[size]:</b> [-128, 127]

*******************
TARGET_INDEX:<b>int8_t</b>
TARGET_TYPE:<b>int</b>

- 13 + size * 2}a + (size * 2 * 2)}stack
- size <= 17 -----> 13 + (34)}a + (76)}stack -------> TOT: 115


<b> int size:</b>&nbsp;&nbsp;[1, 17]; 100 <br>
<b> int a[size]:</b> [-32768, 32767] 

*******************

TARGET_INDEX:<b>int8_t</b>
TARGET_TYPE:<b>long</b>

- 31 + size * 4}a + (size * 4 * 2)}stack
- size <= 6 -----> 31 + (24)a + (48)}stack -------> TOT: 103

<b> long size:</b>&nbsp;&nbsp;[1, 6]; 100 <br>
<b> long a[size]:</b> [-2147483648, 2147483647] 

*******************

TARGET_INDEX:<b>int8_t</b>
TARGET_TYPE:<b>float</b>

- 14 + size * 4}float:a + (size * 2)} int8_t:stack
- size <= 5 -----> 14 + (52) + (26) -------> TOT: 44

<b> int8_t size:</b>&nbsp;&nbsp;&nbsp;[1, 5]; 100 <br>
<b> float a[size]:</b>&nbsp;[-2147483648.0, 2147483647.0]  

