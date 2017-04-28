#pragma once

#include "Grid.h"
#include <curand.h>
#include <curand_kernel.h>
#include "../../04_Montecarlo/01_objet/host/MonteCarlo.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MontecarloMultiGPU
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/
    public:

	MontecarloMultiGPU(const Grid& grid, int nbFlechesTotal, float m);

	virtual ~MontecarloMultiGPU(void);

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

	void run();
	float getResult();

    private:

	Grid grid;
	uint nbThread;
	uint nbFlechesTotal;
	float m;
	uint nbFleches;
	uint nbDevice;
	float result;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
