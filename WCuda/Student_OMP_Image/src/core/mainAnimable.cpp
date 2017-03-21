#include <Animateur_CPU.h>
#include <cudaType_CPU.h>
#include <Provider_I_CPU.h>
#include <stdlib.h>
#include <iostream>

#include "01_Rippling/b_provider/RipplingProvider.h"
#include "04_Raytracing/b_provider/RayTracingProvider.h"

namespace cpu
    {
    class Settings;
    } /* namespace cpu */

using namespace cpu;

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

int mainAnimable(Settings& settings);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static void rippling();
//static void raytracing();

// Tools
template<typename T>
static void animer(Provider_I<T>* ptrProvider, int nbIteration);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainAnimable(Settings& settings)
    {
    cout << "\n[Animable] mode" << endl;

    rippling();
//    mandelbrot();
//    raytracing();

    cout << "\n[Animable] end" << endl;

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void rippling()
    {
    const int NB_ITERATION = 1000;

    RipplingProvider provider;
    animer<uchar4>(&provider, NB_ITERATION);
    }

//void raytracing()
//    {
//    const int NB_ITERATION = 1000;
//
//    RayTracingProvider provider;
//    animer<uchar4>(&provider, NB_ITERATION);
//    }

/*-----------------------------------*\
 |*		Tools	        	*|
 \*-----------------------------------*/

template<typename T>
void animer(Provider_I<T>* ptrProvider, int nbIteration)
    {
    Animateur<T> animateur(ptrProvider, nbIteration);
    animateur.run();
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

