## Banker Algorithm
This README explains the execution flow of the algorithm and how much memory it occupies.

## Test and Implementation Details:
Banker's algorithm is a resource allocation and deadlock avoidance algorithm developed by Edsger Dijkstra that tests 
for safety by simulating the allocation of predetermined maximum possible amounts of all resources, and then 
makes an "s-state" check to test for possible deadlock conditions for all other pending activities, 
before deciding whether allocation should be allowed to continue.

#### Variables
* TARGET_INDEX:  
	- i, j, found, size;
* TARGET_TYPE:
	- SCALAR: 0;  
	- ARRAY: available[size];
	- MATRIX: need[size][size], max[size][size]. allocated[size][size];

#### Occupied Memory
* **#b** = number of bytes used by a given data type (e.g. int8_t = 1, int16_t = 2)  
* **#index** = number of variables used as an index  
* **size** = actual size of the arrays  

* **Eq**: Total Memory > (#index * #b) + (#b * #Scalar) + (size * #b) * #Array + (size * size * #b) * #Matrix

*******************
TARGET_INDEX:<b>uint8_t</b>
TARGET_TYPE:<b>uint8_t</b>

Total Memory > (4 * 1) + (size * 1) * 1 + (size * size * 1) * 3

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):
(4 * 1) + (size * 1) * 1 + (size * size * 1) * 3
4 + size + 3 * size ^ 2 < 2048
size < 25.936

"size": "[2,25];4",
"available[size]": "[0,255]",
"allocated[size][size]": "[0,255]",
"max[size][size]": "[0,255]"

*******************
TARGET_INDEX:<b>uint16_t</b>
TARGET_TYPE:<b>uint16_t</b>

Total Memory > (4 * 2) + (size * 2) * 1 + (size * size * 2) * 3

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):
(4 * 2) + (size * 2) * 1 + (size * size * 2) * 3
8 + 2 * size + 6 * size ^ 2 < 2048
size < 18.27

"size": "[2,18];4",
"available[size]": "[0,255]",
"allocated[size][size]": "[0,255]",
"max[size][size]": "[0,255]"

*******************
TARGET_INDEX:<b>uint32_t</b>
TARGET_TYPE:<b>uint32_t</b>

Total Memory > (4 * 4) + (size * 4) * 1 + (size * size * 4) * 3

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):
(4 * 4) + (size * 4) * 1 + (size * size * 4) * 3
16 + 4 * size + 12 * size ^ 2 < 2048
size < 12.84

"size": "[2,12];4",
"available[size]": "[0,2147483640]",
"allocated[size][size]": "[0,2147483640]",
"max[size][size]": "[0,2147483640]"

*******************
TARGET_INDEX:<b>uint64_t</b>
TARGET_TYPE:<b>uint64_t</b>

Total Memory > (4 * 8) + (size * 8) * 1 + (size * size * 8) * 3

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):
(4 * 8) + (size * 8) * 1 + (size * size * 8) * 3
32 + 8 * size + 24 * size ^ 2 < 2048
size < 9

"size": "[2,9];4",
"available[size]": "[0,9223372036854775807]",
"allocated[size][size]": "[0,9223372036854775807]",
"max[size][size]": "[0,9223372036854775807]"

*******************
TARGET_INDEX:<b>float</b>
TARGET_TYPE:<b>uint32_t</b>

Total Memory > (4 * 4) + (size * 4) * 1 + (size * size * 4) * 3

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):
(4 * 4) + (size * 4) * 1 + (size * size * 4) * 3
16 + 4 * size + 12 * size ^ 2 < 2048
size < 12.84

"size": "[2,12];4",
"available[size]": "[0,2147483640]",
"allocated[size][size]": "[0,2147483640]",
"max[size][size]": "[0,2147483640]"

*******************
TARGET_INDEX:<b>double</b>
TARGET_TYPE:<b>uint64_t</b>

Total Memory > (4 * 8) + (size * 8) * 1 + (size * size * 8) * 3

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):
(4 * 8) + (size * 8) * 1 + (size * size * 8) * 3
32 + 8 * size + 24 * size ^ 2 < 2048
size < 9

"size": "[2,9];4",
"available[size]": "[0,9223372036854775807]",
"allocated[size][size]": "[0,9223372036854775807]",
"max[size][size]": "[0,9223372036854775807]"



