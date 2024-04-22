#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <values.h>
#include <8051.h>
#include <math.h>

#define K 7
#define RATEn 1
#define RATEd 2

typedef float TARGET_TYPE;
typedef unsigned long TARGET_INDEX;

/*	Restituisce la lunghezza del vettore ausiliario per codificare "n" bit ed essere sicuri
	che lo stato finale sia lo "0..00".*/
TARGET_INDEX viterbi_register_lenght(TARGET_INDEX n)
{
	return (n+K-RATEn)+(n+K-RATEn)%RATEn;
}

void reset_values()
{
	P0 = 0;
	P1 = 0;
	P2 = 0;
	P3 = 0;
}

void main()
{
	viterbi_register_lenght(n);
	reset_values();
}