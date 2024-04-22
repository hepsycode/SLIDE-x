## Depth First Search
This README explains the execution flow of the algorithm and how much memory it occupies.

## Test and Implementation Details:
TO BE DEFINED

#### Variables
* TARGET_INDEX:  
	- current, i, tail, head;
* TARGET_TYPE:
	- SCALAR: element;  
	- ARRAY: visited[size];
	- MATRIX: a[size][size];

#### Occupied Memory
* **#b** = number of bytes used by a given data type (e.g. int8_t = 1, int16_t = 2)  
* **#index** = number of variables used as an index  
* **size** = actual size of the arrays  

* **Eq**: Total Memory > (#index * #b) + (#Scalar * #b) + (size * #b) * #Array + (size * size * #b) * #Matrix

*******************************************************************
TARGET_INDEX:<b>uint8_t</b>
TARGET_TYPE:<b>uint8_t</b>

Total Memory > (1 * 1) + (4 * 1) + (size * 1) * 2 + (size * size * 1) * 1

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):
(1 * 1) + (4 * 1) + (size * 1) * 2 + (size * size * 1) * 1 < 2048
5 + 2 * size + size ^ 2 < 2048
size < 44.21

"uint8_t":{
	"size" : "[2,32];2",
	"a[size][size]" : "[-128,127]"
},

*******************************************************************
TARGET_INDEX:<b>uint16_t</b>
TARGET_TYPE:<b>uint16_t</b>

Total Memory > (1 * 2) + (4 * 2) + (size * 2) * 2 + (size * size * 2) * 1

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):
(1 * 2) + (4 * 2) + (size * 2) * 2 + (size * size * 2) * 1 < 2048
10 + 4 * size + 2 * size ^ 2 < 2048
size < 30.937

"uint16_t":{
	"size": "[2,30];2",
	"a[size][size]": "[2,255]"
},

*******************************************************************
TARGET_INDEX:<b>uint32_t</b>
TARGET_TYPE:<b>uint32_t</b>

Total Memory > (1 * 4) + (4 * 4) + (size * 4) * 2 + (size * size * 4) * 1

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):
(1 * 4) + (4 * 4) + (size * 4) * 2 + (size * size * 4) * 1 < 2048
20 + 8 * size + 4 * size ^ 2 < 2048
size < 21.538

"uint32_t":{
	"size": "[2,20];2",
	"a[size][size]": "[2,255]"
},

*******************************************************************
TARGET_INDEX:<b>uint64_t</b>
TARGET_TYPE:<b>uint64_t</b>

Total Memory > (1 * 8) + (4 * 8) + (size * 8) * 2 + (size * size * 8) * 1

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):
(1 * 8) + (4 * 8) + (size * 8) * 2 + (size * size * 8) * 1 < 2048
40 + 16 * size + 8 * size ^ 2 < 2048
size < 14.874

"uint64_t":{
	"size": "[2,14];2",
	"a[size][size]": "[2,255]"
},

*******************************************************************
TARGET_INDEX:<b>float</b>
TARGET_TYPE:<b>uint32_t</b>

Total Memory > (4 * 4) + (size * 4) * 1 + (size * size * 4) * 3

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):
(5 * 4) + (1 * 4) + (size * 4) + (size * size * 4) < 2048
24 + 4 * size + 4 * size ^ 2 < 2048
size < 22

"uint32_t":{
	"size": "[2,20];2",
	"a[size][size]": "[2,255]"
},

*******************************************************************
TARGET_INDEX:<b>double</b>
TARGET_TYPE:<b>uint64_t</b>

Total Memory > (4 * 8) + (size * 8) * 1 + (size * size * 8) * 3

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):
(5 * 8) + (1 * 8) + (size * 8) + (size * size * 8) < 2048
48 + 8 * size + 8 * size ^ 2 < 2048
size < 15.319

"uint64_t":{
	"size": "[2,14];2",
	"a[size][size]": "[2,255]"
},

*******************************************************************