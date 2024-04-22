## Matrix Mutiplication
This README explains the execution flow of the algorithm and how much memory it occupies.

## Test and Implementation Details:
TO BE DEFINED

"TARGET_INDEX size", "TARGET_TYPE a[size][size]", "TARGET_TYPE b[size][size]"

#### Variables
* TARGET_INDEX:  
	- i, j, k;
* TARGET_TYPE:
	- SCALAR: tot;  
	- MATRIX: a[n][n], b[n][size], res[size][size];

#### Occupied Memory
* **#b** = number of bytes used by a given data type (e.g. int8_t = 1, int16_t = 2)  
* **#index** = number of variables used as an index  
* **size** = actual size of the arrays  

* **Eq**: Total Memory > (#index * #b) + (#b * #Scalar) + (size * #b) * #Array + (size * size * #b) * #Matrix

*******************
TARGET_INDEX:<b>uint8_t</b>
TARGET_TYPE:<b>uint8_t</b>

Total Memory > (3 * 1) + (1 * 1) + (size * size * 1) * 3

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):
4 + 3 * x^2 < 2048
x < 26.102


*******************
TARGET_INDEX:<b>uint16_t</b>
TARGET_TYPE:<b>uint16_t</b>

Total Memory > (3 * 2) + (1 * 2) + (size * size * 2) * 3

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):
8 + 6 * x^2 < 2048
x < 18.439


*******************
TARGET_INDEX:<b>uint32_t</b>
TARGET_TYPE:<b>uint32_t</b>

TARGET_INDEX:<b>float</b>
TARGET_TYPE:<b>uint32_t</b>

Total Memory > (3 * 4) + (1 * 4) + (size * size * 4) * 3

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):
16 + 12 * x^2 < 2048
x < 13.012

*******************
TARGET_INDEX:<b>uint64_t</b>
TARGET_TYPE:<b>uint64_t</b>

TARGET_INDEX:<b>double</b>
TARGET_TYPE:<b>uint64_t</b>

Total Memory > (3 * 8) + (1 * 8) + (size * size * 8) * 3

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):
32 + 24 * x^2 < 2048
x < 9.165


