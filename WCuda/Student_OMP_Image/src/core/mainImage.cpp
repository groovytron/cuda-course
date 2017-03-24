#include <GLUTImageViewers_A.h>
#include <ImageOption.h>
#include <Settings_CPU.h>
#include <Viewer_CPU.h>
#include <iostream>

#include "01_Rippling/b_provider/RipplingProvider.h"
#include "02_Mandelbrot/b_provider/MandelbrotProvider.h"
#include "04_Raytracing/b_provider/RayTracingProvider.h"

using namespace cpu;

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported		*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainImage(Settings& settings);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

int mainImage(Settings& settings)
    {
    cout << "\n[Image] mode" << endl;

    GLUTImageViewers::init(settings.getArgc(), settings.getArgv()); // only once

    // ImageOption : (boolean,boolean) : (isSelection,isAnimation)
//    ImageOption zoomable(true);
//    ImageOption nozoomable(false);
    ImageOption zoomable(true, true, true, true);
    ImageOption nozoomable(false, true, true, true);

    Viewer<RipplingProvider> rippling(nozoomable, 0, 0); //  imageOption px py
//    Viewer<MandelbrotProvider> mandelbrot(zoomable, 25, 25); //  imageOption px py
//    Viewer<RayTracingProvider> rayTracing(nozoomable, 0, 0); //  imageOption px py

    GLUTImageViewers::runALL();  // Bloquant, Tant qu'une fenetre est ouverte

    cout << "\n[Image] end" << endl;

    return EXIT_SUCCESS;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

