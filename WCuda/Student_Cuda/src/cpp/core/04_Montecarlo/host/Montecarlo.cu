#include "Montecarlo.h"

#include <iostream>

#include "Device.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

// Kernel 1
__global__
void setup_kernel_rand(curandState* tabDevGenerator, int deviceId);

// Kernel 2
__global__
void montecarlo(curandState* ptrTabDevGenerator, int nbFlecheByThread, int* ptrDevNxTotal);

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

Montecarlo::Montecarlo(const Grid& grid, int nbFlecheByThread) :
	nbFlecheByThread(nbFlecheByThread)
    {
    // Grid
	{
	this->dg = grid.dg;
	this->db = grid.db;
	}

    // TODO: sizeOcteSM, sizeOctetGenerator, sizeOctetResultatFinal
    this->sizeOctetGMResult = sizeof(int);
    this->sizeOctetGMGenerator = sizeof(curandState) * grid.threadCounts();
    this->sizeOctetSM = sizeof(int) * this->db.x; // octet
    // MM
	{

	// MM (malloc Device)
	    {
	    Device::malloc(&ptrDevGMResult, sizeOctetGMResult);
	    Device::memclear(ptrDevGMResult, sizeOctetGMResult);
	    Device::malloc(&ptrDevGMGenerator, sizeOctetGMGenerator);
	    Device::memclear(ptrDevGMGenerator, sizeOctetGMGenerator);
	    }

	Device::lastCudaError("Montecarlo MM (end allocation)"); // temp debug, facultatif
	}

    // Kernel 1. fait ici pour optimisation
setup_kernel_rand<<<this->dg, this->db>>>(ptrDevGMGenerator, Device::getDeviceId());
}

Montecarlo::~Montecarlo(void)
{
//MM (device free)
    {
    Device::free(ptrDevGMResult);
    Device::free(ptrDevGMGenerator);
    Device::lastCudaError("Montecarlo MM (end deallocation)"); // temp debug, facultatif
    }
}

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

void Montecarlo::run()
{
Device::lastCudaError("Montecarlo (before)"); // temp debug
montecarlo<<<dg, db, sizeOctetSM>>>(ptrDevGMGenerator, nbFlecheByThread, ptrDevGMResult); // assynchrone

Device::lastCudaError("Montecarlo (after)");

int result = 0;

// MM (Device -> Host)
    {
    Device::memcpyDToH(&result, ptrDevGMResult, sizeOctetGMResult); // barriere synchronisation implicite
    }

piAt = result;
//	piAt = (result / (float)nbFlecheByThread) * 4.f;
}

int Montecarlo::getResult()
{
return piAt;
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
