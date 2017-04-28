#include <iostream>
#include "Device.h"
#include "cudaTools.h"
#include "MonteCarlo.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

// Kernel 1
extern __global__ void setup_kernel_rand(curandState* tabDevGeneratorGM, int deviceId);
// Kernel 2
extern __global__ void montecarlo(curandState* tabDevGeneratorGM, uint nbFleches,uint m, uint* ptrDevNxTotal);

/*--------------------------------------*\
 |*		Constructeur		*|
 \*-------------------------------------*/

MonteCarlo::MonteCarlo(const Grid& grid, int nbFlechesTotal, float m)
    {

    this->dg = grid.dg;
    this->db = grid.db;

    this->nbThread = Device::nbThread(grid);
    this->nbFlechesTotal = nbFlechesTotal;
    this->m = m;
    this->nbFleches = nbFlechesTotal / nbThread;

    this->ptrDevGeneratorGM = NULL;
    this->sizeOctetGeneratorGM = nbThread * sizeof(curandState);

    this->result = 0;
    this->ptrDevResult = NULL;
    this->sizeInt = sizeof(uint);

    this->sizeTabSM = db.x * sizeof(uint);

    Device::malloc(&ptrDevGeneratorGM, sizeOctetGeneratorGM);
    Device::memclear(ptrDevGeneratorGM, sizeOctetGeneratorGM);

    int id = Device::getDeviceId();

    setup_kernel_rand<<<dg,db>>>(ptrDevGeneratorGM,id);

    Device::malloc(&ptrDevResult, sizeInt);
    cudaMemset(ptrDevResult, 0, sizeInt);
    }

MonteCarlo::~MonteCarlo(void)
    {
    Device::free(ptrDevGeneratorGM);
    Device::free(ptrDevResult);
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

void MonteCarlo::run()
    {

    montecarlo<<<dg,db, sizeTabSM>>>(ptrDevGeneratorGM, nbFleches,m, ptrDevResult); // assynchrone

    Device::memcpyDToH(&montecarloResult, ptrDevResult, sizeInt); // barriere synchronisation implicite

    result = (double) montecarloResult / (double) nbFlechesTotal * m;
    }

float MonteCarlo::getResult()
    {
    return result;
    }

uint MonteCarlo::getMontecarloResult()
    {
    return montecarloResult;
    }
