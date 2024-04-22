## Binary Search
This README explains the execution flow of the algorithm and how much memory it occupies.

## Test and Implementation Details:
TO BE DEFINED

#### Variables
* TARGET_INDEX:  
	- n, m;
* TARGET_TYPE:
	- SCALAR: temp, quotient, de, nu, key, l, r;  
	- ARRAY: arr[size];
	- MATRIX: 0;

#### Occupied Memory
* **#b** = number of bytes used by a given data type (e.g. int8_t = 1, int16_t = 2)  
* **#index** = number of variables used as an index  
* **size** = actual size of the arrays  

* **Eq**: Total Memory > (#index * #b) + (#Scalar * #b) + (size * #b) * #Array + (size * size * #b) * #Matrix

*******************************************************************
TARGET_INDEX:<b>uint8_t</b>
TARGET_TYPE:<b>uint8_t</b>

Total Memory > (2 * 1) + (7 * 1) + (size * 1) * 1

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):


"uint8_t":{

},

*******************************************************************
TARGET_INDEX:<b>uint16_t</b>
TARGET_TYPE:<b>uint16_t</b>

Total Memory > (2 * 1) + (7 * 1) + (size * 1) * 1

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):


"uint16_t":{

},

*******************************************************************
TARGET_INDEX:<b>uint32_t</b>
TARGET_TYPE:<b>uint32_t</b>

Total Memory > (2 * 1) + (7 * 1) + (size * 1) * 1

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):


"uint32_t":{

},

*******************************************************************
TARGET_INDEX:<b>uint64_t</b>
TARGET_TYPE:<b>uint64_t</b>

Total Memory > (2 * 1) + (7 * 1) + (size * 1) * 1

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):


"uint64_t":{

},

*******************************************************************
TARGET_INDEX:<b>float</b>
TARGET_TYPE:<b>uint32_t</b>

Total Memory > (2 * 1) + (7 * 1) + (size * 1) * 1

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):
(2 * 1) + (7 * 1) + (size * 1) * 1 < 2048
XXX < 2048
size < XX

"uint32_t":{

},

*******************************************************************
TARGET_INDEX:<b>double</b>
TARGET_TYPE:<b>uint64_t</b>

Total Memory > (2 * 1) + (7 * 1) + (size * 1) * 1

Atmega328p (Program Memory size 32 KB, RAM 2048 Bytes):


"uint64_t":{

},

*******************************************************************