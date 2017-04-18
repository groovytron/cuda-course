#include <iostream>
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

#include "host/Montecarlo.h"

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useMontecarlo(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useMontecarlo()
    {
    cout << "use" << endl;
    int nbFleche = 9;
    bool isOk = true;

    // Partie interessante Cuda
	{
	cout << "GPU" << endl;
	// Grid cuda
	int mp = Device::getMPCount();
	int coreMP = Device::getCoreCountMP();

	cout << "grid" << endl;

	dim3 dg = dim3(2, 1, 1);  		// grid 1D pour simplifier la réduction intrathread
	dim3 db = dim3(64, 1, 1);   	// bloc 1D pour simplifier la réduction intrathread
	Grid grid(dg, db);

	cout << "montecarlo" << endl;

	Montecarlo montecarlo(grid, nbFleche);

	cout << "before montecarlo run" << endl;

	montecarlo.run();

	cout << "after slice run" << endl;
	cout << "result " << montecarlo.getResult() << endl;
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

