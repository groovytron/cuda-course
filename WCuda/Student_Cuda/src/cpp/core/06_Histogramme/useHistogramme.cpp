#include <iostream>
#include <stdio.h>
#include "Grid.h"
#include "Device.h"

using std::cout;
using std::endl;


#include "host/Histogramme.h"


bool useHistogramme(void);

bool useHistogramme()
    {

	int dataMax = 255;

	int result[dataMax];

	dim3 dg = dim3(64, 1, 1);
	dim3 db = dim3(64, 1, 1);
	Grid grid(dg, db);

	Histogramme histogramme(grid, result, dataMax);
	histogramme.run();

	for (int i = 0; i < dataMax; i++ ) {
	    printf("Element[%d] = %d\n", i, result[i] );
	}

	bool isOk = true;
	return isOk;
    }


