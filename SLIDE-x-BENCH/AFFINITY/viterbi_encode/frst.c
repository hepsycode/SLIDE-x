#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <values.h>
#include <math.h>

#define K 7
#define RATEn 1
#define RATEd 2

typedef float TARGET_TYPE;
typedef unsigned long TARGET_INDEX;

int g[RATEd*K]= {1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1};  /*Matrice contenente le connessioni tra celle del registro e sommatori.*/

TARGET_INDEX bit;
int8_t* bit_aus;
TARGET_INDEX N_bit_aus;
int8_t* bit_out;

void conv_cod(int8_t* buffer,int8_t* codice)
{
	int temp,sommatore,k;
	for (sommatore=0;sommatore<RATEd;sommatore++)
	{
		temp=0;
		for (k=0;k<K;k++)
			temp=(temp+(buffer[K-k-1]&&g[sommatore*K+k]))%2;
		codice[sommatore]=temp;
	}
}

void viterbi_encode(TARGET_INDEX N, TARGET_TYPE bit_in[N])
{
	N_bit_aus=((N+K-RATEn)+(N+K-RATEn)%RATEn)+K-RATEn;
	bit_out = malloc((N_bit_aus-K+1)*sizeof(int8_t));

	bit_aus= malloc(N_bit_aus*sizeof(int8_t));

	for (bit=0;bit<K-RATEn;bit++)
		bit_aus[bit]=0;
	for (bit=0;bit<N;bit++)
		bit_aus[bit+K-RATEn]=bit_in[bit];
	for (bit=N+K-RATEn;bit<N_bit_aus;bit++)
		bit_aus[bit]=0;
	for (bit=0;bit<N_bit_aus-K+1;bit+=RATEn)
		conv_cod(&bit_aus[bit],&bit_out[bit*RATEd/RATEn]);
	free(bit_aus);
	free(bit_out);

}

void main()
{
	viterbi_encode(N, bit_in);
}

