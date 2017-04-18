#include <Indice1D.h>
#include <Indice2D.h>
#include <stdio.h>
#include <curand_kernel.h>
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

// Kernel 2
__global__ void montecarlo(curandState* ptrTabDevGenerator, int nbFlecheByThread, int* ptrDevNxTotal); // ptrDevNxTotal est en GM

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static __device__ void reductionIntraThread(curandState* tabDevGenerator, int n, int* tabSM);

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
void montecarlo(curandState* ptrTabDevGenerator, int nbFlecheByThread, int* ptrDevNxTotal)
    {
    extern __shared__ int tabSM[];
    reductionIntraThread(ptrTabDevGenerator, nbFlecheByThread, tabSM);
    __syncthreads();
    reductionADD<int>(tabSM, ptrDevNxTotal);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__device__ void reductionIntraThread(curandState* tabDevGenerator, int n, int* tabSM)
    {
    const int TID = Indice1D::tidLocal();

    // Global Memory -> Register (optimization)
    curandState localGenerator = tabDevGenerator[TID];

//    float xAlea;
//    float yAlea;
//    int nX = 0;

//    for (int i = 1; i <= n; i++)
//	{
//	xAlea = curand_uniform(&localGenerator);
//	yAlea = curand_uniform(&localGenerator) * 4.f;
//
//	if (y <= f(xAlea))
//	    {
//		// Flèche dans la cible
//	    nX += 1;
//	    }
//	else
//	    {
//		// FLèche hors de la cible
//	    }

	// ...
	// work(xAlea, yAlea); LE CALCUL PEUT SE FAIRE SANS FONCTION
	// ...
//	}

    // Register -> Global Memory
    // Necessaire si on veut utiliser notre generator
    // -dans d’ autre kernel
    // - avec d’ autres nombres aleatoires!

    tabSM[TID] = 1;
    tabDevGenerator[TID] = localGenerator;
    }

__device__ float f(float x)
    {
    return 1 / (1 + x * x);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

