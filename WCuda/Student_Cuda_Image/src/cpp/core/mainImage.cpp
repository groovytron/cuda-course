#include <GLUTImageViewers_A.h>
#include <ImageOption.h>
#include <stdlib.h>
#include <string.h>
#include <Settings_GPU.h>
#include <Viewer_GPU.h>
#include <iostream>

#include "01_Rippling/02_provider/RipplingProvider.h"
#include "02_Mandelbrot_Julia/provider/MandelbrotProvider.h"
#include "03_RayTracing/provider/RayTracingProvider.h"

using namespace gpu;

using std::cout;
using std::endl;
using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
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

int mainImage(Settings& settings)
    {
    cout << "\n[Image] mode" << endl;

    GLUTImageViewers::init(settings.getArgc(), settings.getArgv()); //only once

    // ImageOption : (boolean,boolean) : (isSelection,isAnimation)
    ImageOption zoomable(true, true, true, true);
    ImageOption nozoomable(false, true, true, true);

//    Viewer<RipplingProvider> vague(nozoomable, 0, 0);
//    Viewer<MandelbrotProvider> mandelbrot(zoomable, 400, 0);
    Viewer<RayTracingProvider> raytracing(nozoomable, 800, 0);

    // Common5
    GLUTImageViewers::runALL(); // Bloquant, Tant qu'une fenetre est ouverte

    cout << "\n[Image] end" << endl;

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

