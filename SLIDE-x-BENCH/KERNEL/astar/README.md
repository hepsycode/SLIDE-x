## A* Star Algorithm
This README explains the execution flow of the algorithm and how much memory it occupies.

## Test and Implementation Details:
A * algorithm is a searching algorithm that searches for the shortest path between the initial and the final state. It is used in various applications, such as maps.

In maps the A* algorithm is used to calculate the shortest distance between the source (initial state) and the destination (final state).

#### Variables
* TARGET_INDEX:  
	- i, j, current, goal;
	- came_from[size]
* TARGET_TYPE:
	- SCALAR: tmp1, min, priority, frontier_size;  
	- ARRAY: frontier[size];
	- MATRIX: a[size][size];

#### Occupied Memory
* **#b** = number of bytes used by a given data type (e.g. int8_t = 1, int16_t = 2)  
* **#index** = number of variables used as an index  
* **size** = actual size of the arrays  

* **Eq**: Total Memory > (#index * #b) + (#b * #Scalar) + (size * #b) * #Array + (size * size * #b) * #Matrix
* **Eq**: Total Memory > (4 * #b) + (4 * #b) + (size * #b) * 1 + (size * size * #b) * 1

****************************************************************************
TARGET_INDEX:<b>uint8_t</b>
TARGET_TYPE:<b>uint8_t</b>

Total Memory > (4 * 1) + (4 * 1) + (size * 1) * 1 + (size * size * 1) * 1

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):
(4 * 1) + (4 * 1) + (size * 1) * 1  + (size * size * 1) * 1 < 2048
8 + size + size ^ 2 < 2048
size < 44

"uint8_t":{
	"size": "[2,32];2",
	"a[size][size]": "[-128,127]",
	"goal": "[-128,127];2"
},

MCS 51 (ROM size 64 KB, RAM size 8192 Bytes):
(4 * 1) + (4 * 1) + (size * 1) * 1  + (size * size * 1) * 1 < 128 (256)
8 + size + size ^ 2 < 128 (256)
size < 10.465 (15.255)

"uint8_t":{
	"size": "[2,10];2",
	"a[size][size]": "[-128,127]",
	"goal": "[-128,127];2"
},

****************************************************************************
TARGET_INDEX:<b>uint16_t</b>
TARGET_TYPE:<b>uint16_t</b>

Total Memory > (4 * 2) + (4 * 2) + (size * 2) * 1 + (size * size * 2) * 1

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):
(4 * 2) + (4 * 2) + (size * 2) * 1  + (size * size * 2) * 1 < 2048
16 + 2 * size + 2 * size ^ 2 < 2048
size < 31.378

"uint16_t":{
	"size": "[2,30];2",
	"a[size][size]": "[-32766,32766]",
	"goal": "[2,255];2"
},

MCS 51 (ROM size 64 KB, RAM size 8192 Bytes):
(4 * 2) + (4 * 2) + (size * 2) * 1  + (size * size * 2) * 1 < 128 (256)
16 + 2 * size + 2 * size ^ 2 < 128 (256)
size < 7 (10.465)

"uint16_t":{
	"size": "[2,7];2",
	"a[size][size]": "[-32766,32766]",
	"goal": "[2,255];2"
},

****************************************************************************
TARGET_INDEX:<b>uint32_t</b>
TARGET_TYPE:<b>uint32_t</b>

Total Memory > (4 * 4) + (4 * 4) + (size * 4) * 1 + (size * size * 4) * 1

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):
(4 * 4) + (4 * 4) + (size * 4) * 1  + (size * size * 4) * 1 < 2048
32 + 4 * size + 4 * size ^ 2 < 2048
size < 21.955

"uint32_t":{
	"size": "[2,20];2",
	"a[size][size]": "[-2147483640,2147483640]",
	"goal": "[2,255];2"
},

MCS 51 (ROM size 64 KB, RAM size 8192 Bytes):
(4 * 4) + (4 * 4) + (size * 4) * 1  + (size * size * 4) * 1 < 128 (256)
32 + 4 * size + 4 * size ^ 2 < 128 (256)
size < 4.424 (7)

"uint32_t":{
	"size": "[2,32];2",
	"a[size][size]": "[-32766,32766]",
	"goal": "[2,255];2"
},

****************************************************************************
TARGET_INDEX:<b>uint64_t</b>
TARGET_TYPE:<b>uint64_t</b>

Total Memory > (4 * 8) + (4 * 8) + (size * 8) * 1 + (size * size * 8) * 1

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):
(4 * 8) + (4 * 8) + (size * 8) * 1  + (size * size * 8) * 1 < 2048
64 + 8 * size + 8 * size ^ 2 < 2048
size < 15.25

"uint64_t":{
	"size": "[2,15];2",
	"a[size][size]": "[-9223372036854775808,922337203685477580]",
	"goal": "[2,255];2"
},

MCS 51 (ROM size 64 KB, RAM size 8192 Bytes):
(4 * 8) + (4 * 8) + (size * 8) * 1  + (size * size * 8) * 1 < 128 (256) (8192)
64 + 8 * size + 8 * size ^ 2 < 8192
size < 2.372 (4.424) (31.378)

"uint64_t":{
	"size": "[2,30];2",
	"a[size][size]": "[-9223372036854775808,922337203685477580]",
	"goal": "[2,255];2"
},

****************************************************************************
TARGET_INDEX:<b>float</b>
TARGET_TYPE:<b>uint32_t</b>

Total Memory > (4 * 4) + (4 * 4) + (size * 4) * 1 + (size * size * 4) * 1

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):
(4 * 4) + (4 * 4) + (size * 4) * 1  + (size * size * 4) * 1 < 2048
32 + 4 * size + 4 * size ^ 2 < 2048
size < 21.955

"uint32_t":{
	"size": "[2,21];2",
	"a[size][size]": "[-2147483640,2147483640]",
	"goal": "[2,255];2"
},

MCS 51 (ROM size 64 KB, RAM size 8192 Bytes):
(4 * 4) + (4 * 4) + (size * 4) * 1  + (size * size * 4) * 1 <  128 (256) (8192)
32 + 4 * size + 4 * size ^ 2 <  128 (256) (8192)
size < 4.424 (7) (44.669)

"uint32_t":{
	"size": "[2,32];2",
	"a[size][size]": "[-32766,32766]",
	"goal": "[2,255];2"
},

****************************************************************************
TARGET_INDEX:<b>double</b>
TARGET_TYPE:<b>uint64_t</b>

Total Memory > (4 * 8) + (4 * 8) + (size * 8) * 1 + (size * size * 8) * 1

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):
(4 * 8) + (4 * 8) + (size * 8) * 1  + (size * size * 8) * 1 < 2048
64 + 8 * size + 8 * size ^ 2 < 2048
size < 15.25

"uint64_t":{
	"size": "[2,15];2",
	"a[size][size]": "[-9223372036854775808,922337203685477580]",
	"goal": "[2,255];2"
},

MCS 51 (ROM size 64 KB, RAM size 8192 Bytes):
(4 * 8) + (4 * 8) + (size * 8) * 1  + (size * size * 8) * 1 <  128 (256) (8192)
64 + 8 * size + 8 * size ^ 2 <  128 (256) (8192)
size < 2.372 (4.424) (31.378)

"uint64_t":{
	"size": "[2,30];2",
	"a[size][size]": "[-9223372036854775808,922337203685477580]",
	"goal": "[2,255];2"
},

****************************************************************************