#include <iostream>
#include "Device.h"
#include "cudaTools.h"
#include "DataCreator.h"

#include "Histogramme.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void histogramme(int* ptrTabInput, uint length, int* ptrHistogrammeGM);

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
|*		Constructeur		*|
 \*-------------------------------------*/

Histogramme::Histogramme(const Grid& grid, int* ptrResult, int dataMax)
    {

    this->dg = grid.dg;
    this->db = grid.db;

    this->ptrResult = ptrResult;

    DataCreator dataCreator(dataMax);
    this->data = dataCreator.getTabData();
    this->length = dataCreator.getLength();

    // Memory management
    this->sizeOctetResult = sizeof(int) * dataMax;
    this->sizeOctetData = sizeof(int) * this->length;

    Device::malloc(&ptrTabInput, sizeOctetData);
    Device::memclear(ptrTabInput, sizeOctetData);
    Device::memcpyHToD(ptrTabInput, data, sizeOctetData);

    Device::malloc(&ptrTabOutput, sizeOctetResult);
    Device::memclear(ptrTabOutput, sizeOctetResult);

    }

Histogramme::~Histogramme(void)
    {
    Device::free(ptrTabInput);
    Device::free(ptrTabOutput);
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

void Histogramme::run()
    {
    Device::lastCudaError("histogramme (before)");
    histogramme<<<dg,db, sizeOctetResult>>>(ptrTabInput, length, ptrTabOutput);
    Device::lastCudaError("histogramme (after)");

    Device::synchronize();

    Device::memcpyDToH(ptrResult, ptrTabOutput, sizeOctetResult);
    }

