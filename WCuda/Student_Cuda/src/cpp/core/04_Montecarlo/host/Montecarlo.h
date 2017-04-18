#pragma once

#include <curand_kernel.h>

#include "cudaTools.h"
#include "Grid.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Montecarlo
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	// Hypothèse grid 1D
	Montecarlo(const Grid& grid, int nbFlecheByThread);

	virtual ~Montecarlo(void);

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

	void run();
	int getResult();

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	dim3 dg;
	dim3 db;
	int nbFlecheByThread;

	// Inputs/Outputs
//	float result;

// Tools
	size_t sizeOctetSM;
	size_t sizeOctetGMGenerator;
	size_t sizeOctetGMResult;

	int* ptrDevGMResult;
	curandState* ptrDevGMGenerator;

	double piAt; // Resultat final
    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
