#include "Indice1D.h"
#include "reductionADD.h"
#include <curand_kernel.h>

__global__ void montecarlo(curandState* tabDevGeneratorGM, uint nbALancer, uint m, uint* ptrDevNxTotal);

__device__ float f(float x);

static __device__ void reductionIntraThread(curandState* tabDevGeneratorGM, uint nbALancer, uint m, uint* ptrDevNxTotal, uint* tabSM);

__global__ void montecarlo(curandState* tabDevGeneratorGM, uint nbALancer, uint m, uint* ptrDevNxTotal)
    {
    extern __shared__ uint
    tabSM[];

    reductionIntraThread(tabDevGeneratorGM, nbALancer, m, ptrDevNxTotal, tabSM);

    __syncthreads();

    reductionADD < uint > (tabSM, ptrDevNxTotal);
    }

static __device__ void reductionIntraThread(curandState* tabDevGeneratorGM, uint nbALancer, uint m, uint* ptrDevNxTotal, uint* tabSM)
    {
    const int NB_THREAD = Indice1D::nbThread();
    const int TID = Indice1D::tid();
    const int TID_LOCAL = Indice1D::tidLocal();

    curandState localGenerator = tabDevGeneratorGM[TID];

    int nx = 0;
    float x;
    float y;

    for(int i = 0; i < nbALancer; i++)
	{

	x = curand_uniform(&localGenerator);
	y = curand_uniform(&localGenerator) * m;

	if (y < f(x))
	    {
	    nx ++;
	    }
	}

    tabSM[TID_LOCAL] = nx;
    tabDevGeneratorGM[TID_LOCAL] = localGenerator;
    }

__device__ float f(float x)
    {
    return 4 / (1 + x * x);
    }
