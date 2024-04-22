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

TARGET_INDEX N; /*Indica il numero di bit da codificare.*/
TARGET_INDEX N_CODIFICATI; /*Indica il numero di bit codificati.*/
int* g;  /*Matrice contenente le connessioni tra celle del registro e sommatori.*/

/*	Restituisce la lunghezza del vettore ausiliario per codificare "n" bit ed essere sicuri
	che lo stato finale sia lo "0..00".*/
TARGET_INDEX lunghezza_registro(TARGET_INDEX n)
{
	return (n+K-RATEn)+(n+K-RATEn)%RATEn;
}

/* Restituisce il numero di bit codificati dal codificatore se in ingresso ce ne sono "n".*/
TARGET_INDEX viterbi_getn(TARGET_INDEX n)
{
	return lunghezza_registro(n)/RATEn*RATEd;
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
	viterbi_getn(n);
	reset_values();
}