#include <GLUTImageViewers_A.h>
#include <ImageOption.h>
#include <RayTracingProvider.h>
#include <RipplingProvider.h>
#include <MandelbrotProvider.h>
#include <stdlib.h>
#include <string.h>
#include <Settings_GPU.h>
#include <Viewer_GPU.h>
#include <iostream>

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
 |*		Public			*
 \*-------------------------------------*/

int mainImage(Settings& settings)
    {
    cout << "\n[Image] mode" << endl;

    GLUTImageViewers::init(settings.getArgc(), settings.getArgv()); //only once

    // ImageOption : (boolean,boolean) : (isSelection,isAnimation)
//    ImageOption zoomable(true);
//    ImageOption nozoomable(false);
    ImageOption zoomable(true, true, true, true);
    ImageOption nozoomable(false, true, true, true);

    Viewer<RipplingProvider> vague(nozoomable, 0, 0);
    Viewer<MandelbrotProvider> mandelbrot(zoomable, 450, 0);
    Viewer<RayTracingProvider> raytracing(nozoomable, 900, 0);

    // Common
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

