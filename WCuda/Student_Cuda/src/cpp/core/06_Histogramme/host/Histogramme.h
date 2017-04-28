#pragma once

#include "Grid.h"
#include <curand.h>
#include <curand_kernel.h>

class Histogramme
    {

    public:

	Histogramme(const Grid& grid, int* ptrResult, int dataMax);

	virtual ~Histogramme(void);

	void run();

    private:
	dim3 dg;
	dim3 db;

	// Inputs/Outputs
	int* ptrTabInput;

	// Tools
	int* ptrResult;
	size_t sizeOctetData;
	size_t sizeOctetResult;
	int* data;
	int length;

	// Ouputs
	int* ptrTabOutput;
    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
