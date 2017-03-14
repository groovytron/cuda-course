#include "Mandelbrot.h"

#include <IndiceTools_CPU.h>
#include <omp.h>
#include <OmpTools.h>
#include <ParallelPatern.h>
#include <iostream>

#include "../../01_Rippling/a_animable/math/RipplingMath.h"
#include "math/MandelbrotMath.h"

namespace cpu
    {
    class IndiceTools;
    } /* namespace cpu */

using cpu::IndiceTools;

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

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
 |*		Public			*|
 \*-------------------------------------*/

Mandelbrot::Mandelbrot(uint w, uint h, DomaineMath domaineMath) :
	Animable_I<uchar4>(w, h, "Mandelbrot_OMP_rgba_uchar4")
    {
    // Input
    this->dt = dt;  // animation
    this->domaineMath = domaineMath;

    // Tools
    this->t = 0;					// protected dans super classe Animable
    this->parallelPatern = ParallelPatern::OMP_MIXTE;   // protected dans super classe Animable

    // OMP
    cout << "\n[Rippling] : OMP : nbThread = " << this->nbThread << endl; // protected dans super classe Animable
    }

Mandelbrot::~Mandelbrot(void)
    {
    // rien
    }

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Override
 */
void Mandelbrot::animationStep()
    {
    t += dt;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * Override (code naturel omp)
 * Image non zoomable : domaineMath pas use ici
 */
void Mandelbrot::processForAutoOMP(uchar4* ptrTabPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    MandelbrotMath mandelbrotMath(w);
    const int N = 12;

#pragma omp parallel for
    for (int i = 0; i < h; i++)
	{
	for (int j = 0; j < w; j++)
	    {
	    int s = IndiceTools::toS(w, i, j);
	    mandelbrotMath.colorIJ(&ptrTabPixels[s], i, j, N);
	    }
	}
    }

/**
 * Override (code entrainement cuda)
 * Image non zoomable : domaineMath pas use ici
 */
void Mandelbrot::processEntrelacementOMP(uchar4* ptrTabPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    const int WH = w * h;

//    RipplingMath ripplingMath = RipplingMath(w); // v1

    MandelbrotMath mandelbrotMath(w); // v2

#pragma omp parallel
	{
	const int NB_THREAD = OmpTools::getNbThread();
	const int TID = OmpTools::getTid();
	int s = TID;
	int i;
	int j;

	while (s < WH)
	    {
	    IndiceTools::toIJ(s, w, &i, &j);
	    mandelbrotMath.colorIJ(&ptrTabPixels[s], i, j, t);

	    s += NB_THREAD;
	    }
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

