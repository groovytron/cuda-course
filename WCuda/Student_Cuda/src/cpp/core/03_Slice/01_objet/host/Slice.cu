#include "Slice.h"

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

//extern __global__ void slice(float* ptrDevV1, float* ptrDevV2, float* ptrDevW,int n);
extern __global__ void slice(float* ptrDevGMResult, int nbSlice);

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

Slice::Slice(const Grid& grid, int nbSlice) :
	nbSlice(nbSlice)
    {
    // Grid
	{
	this->dg = grid.dg;
	this->db = grid.db;
	}

    this->sizeOctetGM = sizeof(float);
    this->sizeOctetSM = sizeof(float) * this->db.x; // octet
    // MM
	{

	// MM (malloc Device)
	    {
	    Device::malloc(&ptrDevGMResult, sizeOctetGM);
	    Device::memclear(ptrDevGMResult, sizeOctetGM);
	    }

	Device::lastCudaError("Slice MM (end allocation)"); // temp debug, facultatif
	}

    }

Slice::~Slice(void)
    {
    //MM (device free)
	{
	Device::free(ptrDevGMResult);
	Device::lastCudaError("Slice MM (end deallocation)"); // temp debug, facultatif
	}
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

void Slice::run()
    {
    Device::lastCudaError("slice (before)"); // temp debug
    slice<<<dg, db, sizeOctetSM>>>(ptrDevGMResult, nbSlice); // assynchrone
    Device::lastCudaError("slice (after)");

    // MM (Device -> Host)
	{
	Device::memcpyDToH(&result, ptrDevGMResult, sizeOctetGM); // barriere synchronisation implicite
	}

    }

float Slice::getResult()
    {
    return result;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
