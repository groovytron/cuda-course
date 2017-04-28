#include <iostream>
#include <limits>
#include "Grid.h"
#include "Device.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

#include "host/Slice.h"

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useSlice(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useSlice()
    {
    cout << "use" << endl;
    int nbSlice = 10000;
    bool isOk = true;

    // Partie interessante GPGPU
	{
	cout << "GPU" << endl;
	// Grid cuda
	int mp = Device::getMPCount();
	int coreMP = Device::getCoreCountMP();

	cout << "grid" << endl;

	dim3 dg = dim3(512, 1, 1);  		// grid 1D pour simplifier la réduction intrathread
	dim3 db = dim3(512, 1, 1);   	// bloc 1D pour simplifier la réduction intrathread
	Grid grid(dg, db);

	cout << "slice" << endl;

	Slice slice(grid, nbSlice);

	cout << "before slice run" << endl;

	slice.run();

	cout << "after slice run" << endl;
	// TODO: pintf(slice.getResult()) du résultat
	printf("result %f", slice.getResult());
	}

    cout << "use end" << endl;

    return isOk;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

