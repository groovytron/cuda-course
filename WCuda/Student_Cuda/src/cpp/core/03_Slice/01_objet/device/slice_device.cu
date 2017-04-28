#include <Indice1D.h>
#include <Indice2D.h>
#include <stdio.h>
#include "reductionADD.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void slice(float* ptrDevGMResult, int nbSlice);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static __device__ float fpi(float x);
static __device__ void reductionIntraThread(float* tabSM, int nbSlice);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * output : void required !!
 */
__global__
void slice(float* ptrDevGMResult, int nbSlice)
    {
    extern __shared__ float tabSM[];
    reductionIntraThread(tabSM, nbSlice);
    __syncthreads();
    reductionADD<float>(tabSM, ptrDevGMResult);
//    reductionAdd<float>(tabSM, ptrDevGMResult);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__device__ void reductionIntraThread(float* tabSM, int nbSlice)
    {
    const int NB_THREAD = Indice1D::nbThread();
    const int TID = Indice1D::tid();

    const int TID_LOCAL = Indice1D::tidLocal();
    const float DX = 1.0f / (float) nbSlice;
    float sommeLocale = 0;

    int s = TID;
    while (s < nbSlice)
	{
	float x = s * DX;
	sommeLocale += fpi(x);
	s += NB_THREAD;
	}

    tabSM[TID_LOCAL] = 4 *sommeLocale * DX;
    }

__device__ float fpi(float x)
    {
    return 1 / (1. + x * x);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

