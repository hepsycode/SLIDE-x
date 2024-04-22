## function_name
This README explains the execution flow of the algorithm and how much memory it occupies.

## Test and Implementation Details:
TO BE DEFINED

TARGET_INDEX n, TARGET_TYPE alpha, TARGET_TYPE beta, TARGET_TYPE A[n][n], TARGET_TYPE B[n][n], TARGET_TYPE C[n][n], TARGET_TYPE D[n][n]

#### Variables
* TARGET_INDEX:  
	- n;
* TARGET_TYPE:
	- SCALAR: alpha, beta;  
	- MATRIX: A[n][n], B[n][size], C[size][size], D[size][size], tmp[size][size];

#### Occupied Memory
* **#b** = number of bytes used by a given data type (e.g. int8_t = 1, int16_t = 2)  
* **#index** = number of variables used as an index  
* **size** = actual size of the arrays  

* **Eq**: Total Memory > (#index * #b) + (#b * #Scalar) + (size * #b) * #Array + (size * size * #b) * #Matrix

*******************
TARGET_INDEX:<b>uint8_t</b>
TARGET_TYPE:<b>uint8_t</b>

Total Memory > (1 * 1) + (2 * 1) * 1 + (size * size * 1) * 5

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):
3 + 5 * x^2 < 2048
x < 20.223


*******************
TARGET_INDEX:<b>uint16_t</b>
TARGET_TYPE:<b>uint16_t</b>

Total Memory > (1 * 2) + (2 * 2) * 1 + (size * size * 2) * 5

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):
6 + 10 * x^2 < 2048
x < 14.289


*******************
TARGET_INDEX:<b>uint32_t</b>
TARGET_TYPE:<b>uint32_t</b>

TARGET_INDEX:<b>float</b>
TARGET_TYPE:<b>uint32_t</b>

Total Memory > (1 * 4) + (2 * 4) * 1 + (size * size * 4) * 5

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):
12 + 20 * x^2 < 2048
x < 10.089

*******************
TARGET_INDEX:<b>uint64_t</b>
TARGET_TYPE:<b>uint64_t</b>

TARGET_INDEX:<b>double</b>
TARGET_TYPE:<b>uint64_t</b>

Total Memory > (1 * 8) + (2 * 8) * 1 + (size * size * 8) * 5

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):
x < 7.113


