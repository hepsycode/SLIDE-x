## function_name
This README explains the execution flow of the algorithm and how much memory it occupies.

## Test and Implementation Details:
TO BE DEFINED

#### Variables
* TARGET_INDEX:  
	- XXX, size;
* TARGET_TYPE:
	- SCALAR: XXX;  
	- ARRAY: XX[size];
	- MATRIX: X[size][size], X[size][size], X[size][size];

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


*******************
TARGET_INDEX:<b>uint16_t</b>
TARGET_TYPE:<b>uint16_t</b>

Total Memory > (4 * 2) + (size * 2) * 1 + (size * size * 2) * 3

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):


*******************
TARGET_INDEX:<b>uint32_t</b>
TARGET_TYPE:<b>uint32_t</b>

Total Memory > (4 * 4) + (size * 4) * 1 + (size * size * 4) * 3

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):


*******************
TARGET_INDEX:<b>uint64_t</b>
TARGET_TYPE:<b>uint64_t</b>

Total Memory > (4 * 8) + (size * 8) * 1 + (size * size * 8) * 3

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):


*******************
TARGET_INDEX:<b>float</b>
TARGET_TYPE:<b>uint32_t</b>

Total Memory > (4 * 4) + (size * 4) * 1 + (size * size * 4) * 3

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):


*******************
TARGET_INDEX:<b>double</b>
TARGET_TYPE:<b>uint64_t</b>

Total Memory > (4 * 8) + (size * 8) * 1 + (size * size * 8) * 3

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):




