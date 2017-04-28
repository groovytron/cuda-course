#pragma once

#include "Grid.h"
#include <curand.h>
#include <curand_kernel.h>

class MonteCarlo
    {
	/*--------------------------------------*\
	 |*		Public			*|
	 \*-------------------------------------*/

    public:

	MonteCarlo(const Grid& grid, int nbFlechesTotal, float m);

	virtual ~MonteCarlo(void);

	void run();

	float getResult();
	uint getMontecarloResult();

	/*--------------------------------------*\
	 |*		Private			*|
	 \*-------------------------------------*/

    private:

	// Inputs
	dim3 dg;
	dim3 db;
	uint nbThread;
	uint nbFlechesTotal;
	float m;
	uint nbFleches;

	// Outputs
	float result;
	uint montecarloResult;

	// Tools
	uint* ptrDevResult;
	size_t sizeInt;

	// Memory management
	curandState* ptrDevGeneratorGM;
	size_t sizeOctetGeneratorGM;
	size_t sizeTabSM;
    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
