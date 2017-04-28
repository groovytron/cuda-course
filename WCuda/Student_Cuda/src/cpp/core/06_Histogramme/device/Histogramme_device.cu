#include "Indice2D.h"
#include "Indice1D.h"
#include "reductionADD.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

__device__ void reductionIntraThread(int* tabSM, int* ptrTabIn, uint lenght);

__device__ void reductionInterBlock(int* tabSM, int* ptrHistogrammeGM);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
|*		Constructeur		*|
 \*-------------------------------------*/

__global__ void histogramme(int* ptrTabIn, uint lenght, int* ptrHistogrammeGM)
    {
    extern __shared__ int tabSM[];

    reductionIntraThread(tabSM, ptrTabIn, lenght);

    __syncthreads();

    reductionInterBlock(tabSM, ptrHistogrammeGM);
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

__device__ void reductionIntraThread(int* tabSM, int* ptrTabIn, uint lenght)
    {
    const int NB_THREAD = Indice2D::nbThread();
    const int TID = Indice2D::tid();
    const int TID_LOCAL = Indice1D::tidLocal();

    int s = TID;

    while (s < lenght)
	{
	int value = ptrTabIn[s];
	atomicAdd(&tabSM[value], 1);
	s += NB_THREAD;
	}
    }

__device__ void reductionInterBlock(int* tabSM, int* ptrHistogrammeGM)
    {
    if (Indice2D::tidLocal() == 0)
	{
	for (int i = 0; i < 256; i++)
	    {
	    atomicAdd(&ptrHistogrammeGM[i], tabSM[i]);
	    }
	}
    }
