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
TARGET_INDEX get_N_viterbi(TARGET_INDEX n)
{
	return lunghezza_registro(n)/RATEn*RATEd;
}

/*	Svolge tutte le operazioni necessarie per inizializzare il codificatore
	e decodificatore di Viterbi. "n" indica il numero di bit da codificare.*/
TARGET_INDEX viterbi_init(TARGET_INDEX n)
{
	int s,r;
	//int* numBase8;
	N=n;
	N_CODIFICATI=get_N_viterbi(N);
	g=(int*)malloc(RATEd*K*sizeof(int));

/*	In base alla constraint lenght "K" e al numero di sommatori "RATEd" sceglie i migliori
	generatori per connessioni tra le celle del registro e i sommatori,*/
	switch (K)
	{
		case 3:
			switch (RATEd)
			{
				case 2:
					g[0*K+0]=1; g[0*K+1]=1; g[0*K+2]=1; //sommatore 1
					g[1*K+0]=1; g[1*K+1]=0; g[1*K+2]=1; //sommatore 2
					break;
				case 3:
					g[0*K+0]=1; g[0*K+1]=1; g[0*K+2]=1; //sommatore 1
					g[1*K+0]=1; g[1*K+1]=1; g[1*K+2]=1; //sommatore 2
					g[2*K+0]=1; g[2*K+1]=0; g[2*K+2]=1; //sommatore 3
					break;
				default:
					//printf("Non esistono dei generatori associati a K=%d con RATEd=%d.",K,RATEd);
					break;
			}
			break;
		case 4:
			switch (RATEd)
			{
				case 2:
					g[0*K+0]=1; g[0*K+1]=1; g[0*K+2]=1; g[0*K+3]=1; //sommatore 1
					g[1*K+0]=1; g[1*K+1]=1; g[1*K+2]=0; g[1*K+3]=1; //sommatore 2
					break;
				case 3:
					g[0*K+0]=1; g[0*K+1]=1; g[0*K+2]=1; g[0*K+3]=1; //sommatore 1
					g[1*K+0]=1; g[1*K+1]=1; g[1*K+2]=0; g[1*K+3]=1; //sommatore 2
					g[2*K+0]=1; g[2*K+1]=0; g[2*K+2]=1; g[2*K+3]=1; //sommatore 3
					break;
				default:
					//printf("Non esistono dei generatori associati a K=%d con RATEd=%d.",K,RATEd);
					break;
			}
			break;
		case 5:
			switch (RATEd)
			{
				case 2:
					g[0*K+0]=1; g[0*K+1]=1; g[0*K+2]=1; g[0*K+3]=1; g[0*K+4]=1; //sommatore 1
					g[1*K+0]=1; g[1*K+1]=0; g[1*K+2]=1; g[1*K+3]=1; g[1*K+4]=1; //sommatore 2
					break;
				case 3:
					g[0*K+0]=1; g[0*K+1]=1; g[0*K+2]=1; g[0*K+3]=1; g[0*K+4]=1; //sommatore 1
					g[1*K+0]=1; g[1*K+1]=1; g[1*K+2]=0; g[1*K+3]=1; g[1*K+4]=1; //sommatore 2
					g[2*K+0]=1; g[2*K+1]=0; g[2*K+2]=1; g[2*K+3]=0; g[2*K+4]=1; //sommatore 3
					break;
				default:
					//printf("Non esistono dei generatori associati a K=%d con RATEd=%d.",K,RATEd);
					break;
			}
			break;
		case 6:
			switch (RATEd)
			{
				case 2:
					g[0*K+0]=1; g[0*K+1]=1; g[0*K+2]=1; g[0*K+3]=1; g[0*K+4]=0; g[0*K+5]=1; //sommatore 1
					g[1*K+0]=1; g[1*K+1]=0; g[1*K+2]=1; g[1*K+3]=1; g[1*K+4]=1; g[1*K+5]=1; //sommatore 2
					break;
				case 3:
					g[0*K+0]=1; g[0*K+1]=1; g[0*K+2]=1; g[0*K+3]=1; g[0*K+4]=0; g[0*K+5]=1; //sommatore 1
					g[1*K+0]=1; g[1*K+1]=1; g[1*K+2]=0; g[1*K+3]=0; g[1*K+4]=1; g[1*K+5]=1; //sommatore 2
					g[2*K+0]=1; g[2*K+1]=0; g[2*K+2]=0; g[2*K+3]=1; g[2*K+4]=1; g[2*K+5]=1; //sommatore 3
					break;
				default:
					//printf("Non esistono dei generatori associati a K=%d con RATEd=%d.",K,RATEd);
					break;
			}
			break;
		case 7:
			switch (RATEd)
			{
				case 2:
					g[0*K+0]=1; g[0*K+1]=1; g[0*K+2]=1; g[0*K+3]=1; g[0*K+4]=0; g[0*K+5]=0; g[0*K+6]=1; //sommatore 1
					g[1*K+0]=1; g[1*K+1]=0; g[1*K+2]=1; g[1*K+3]=1; g[1*K+4]=0; g[1*K+5]=1; g[1*K+6]=1; //sommatore 2
					break;
				case 3:
					g[0*K+0]=1; g[0*K+1]=1; g[0*K+2]=1; g[0*K+3]=1; g[0*K+4]=0; g[0*K+5]=0; g[0*K+6]=1; //sommatore 1
					g[1*K+0]=1; g[1*K+1]=1; g[1*K+2]=1; g[1*K+3]=0; g[1*K+4]=1; g[1*K+5]=0; g[1*K+6]=1; //sommatore 2
					g[2*K+0]=1; g[2*K+1]=0; g[2*K+2]=1; g[2*K+3]=1; g[2*K+4]=0; g[2*K+5]=1; g[2*K+6]=1; //sommatore 3
					break;
				default:
					//printf("Non esistono dei generatori associati a K=%d con RATEd=%d.",K,RATEd);
					break;
			}
			break;
		case 8:
			switch (RATEd)
			{
				case 2:
					g[0*K+0]=1; g[0*K+1]=1; g[0*K+2]=1; g[0*K+3]=1; g[0*K+4]=1; g[0*K+5]=0; g[0*K+6]=0; g[0*K+7]=1; //sommatore 1
					g[1*K+0]=1; g[1*K+1]=0; g[1*K+2]=1; g[1*K+3]=0; g[1*K+4]=0; g[1*K+5]=1; g[1*K+6]=1; g[1*K+7]=1; //sommatore 2
					break;
				case 3:
					g[0*K+0]=1; g[0*K+1]=1; g[0*K+2]=1; g[0*K+3]=1; g[0*K+4]=0; g[0*K+5]=1; g[0*K+6]=1; g[0*K+7]=1; //sommatore 1
					g[1*K+0]=1; g[1*K+1]=1; g[1*K+2]=0; g[1*K+3]=1; g[1*K+4]=1; g[1*K+5]=0; g[1*K+6]=0; g[1*K+7]=1; //sommatore 2
					g[2*K+0]=1; g[2*K+1]=0; g[2*K+2]=0; g[2*K+3]=1; g[2*K+4]=0; g[2*K+5]=1; g[2*K+6]=0; g[2*K+7]=1; //sommatore 3
					break;
				default:
					//printf("Non esistono dei generatori associati a K=%d con RATEd=%d.",K,RATEd);
					break;
			}
			break;
		default:
				//printf("Non esistono dei generatori associati a K=%d.",K);
				break;
	}

	//printf("Viterbi: rate=%d/%d  K=%d N=%d ",RATEn,RATEd,K,N_CODIFICATI);
	//printf("\nGeneratori: ");
	/* for (s=0;s<RATEd;s++)
	{
		for (r=0;r<K;r++)
			printf("%d",g[s*K+r]);
		printf(" ");
	}*/
	/*for (s=0;s<RATEd;s++)
	{
		numBase8=bin2baseN(&g[s*K],K,3);
		for (r=0;r<(K+(3-K%3))/3;r++)
			printf("%d",numBase8[r]);
		printf("   ");
		free(numBase8);
	}*/
	//printf("\n");
	return N_CODIFICATI;
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
	viterbi_init(n);
	reset_values();
}