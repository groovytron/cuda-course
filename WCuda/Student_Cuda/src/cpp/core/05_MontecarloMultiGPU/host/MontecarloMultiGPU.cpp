#include <iostream>
#include "Device.h"
#include "cudaTools.h"

#include "MontecarloMultiGPU.h"

using std::cout;
using std::endl;

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
 |*		Constructeur			*|
 \*-------------------------------------*/

MontecarloMultiGPU::MontecarloMultiGPU(const Grid& grid, int nbFlechesTotal, float m)
    {
    this->grid = grid;
    this->nbThread = Device::nbThread(grid);
    this->nbFlechesTotal = nbFlechesTotal;
    this->m = m;
    this->nbFleches = nbFlechesTotal / nbThread;
    this->nbDevice = Device::getDeviceCount();
    this->result = 0.0f;
    }

MontecarloMultiGPU::~MontecarloMultiGPU(void)
    {

    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

void MontecarloMultiGPU::run()
    {
    long somme = 0;
#pragma omp parallel for reduction(+:somme)
    for (int i = 0; i < nbDevice; i++)
	{
	Device::setDevice(i);
	MonteCarlo mc(grid, nbFlechesTotal / nbDevice, m);
	mc.run();
	somme = mc.getMontecarloResult();
	}

    result = (double) somme * m / (double) nbFlechesTotal;

    }

float MontecarloMultiGPU::getResult()
    {
    return result;
    }
