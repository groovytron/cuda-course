#pragma once

#include <math.h>
#include "MathTools.h"

#include "ColorTools_GPU.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RipplingMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ RipplingMath(int w, int h)
	    {
	    this->dim2 = w / 2;
	    }

	// constructeur copie automatique car pas pointeur dans VagueMath

	__device__
	      virtual ~RipplingMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__
	void colorIJ(uchar4* ptrColor, int i, int j, float t)
	    {
	    uchar levelGris;

	    f(&levelGris, i, j, t); // update levelGris

//	    levelGris = 0;

	    ptrColor->x = levelGris;
	    ptrColor->y = levelGris;
	    ptrColor->z = levelGris;

	    ptrColor->w = 255; // opaque
	    }

    private:

	__device__
	void f(uchar* ptrLevelGris, int i, int j, float t)
	    {
	    // TODO cf fonction math pdf
	    // use focntion dij ci-dessous

	    // Note
	    //		Si code OMP focntionnel:
	    // 			Step1 : Delete le contenur de ce fichier (si!),
	    // 			Step2 : Copie-past le contenu de RipplingMath.h de omp,
	    // 			Step3 : Ajouter __device__  devant methode et constructeur!
	    float dijResult = dij(i, j) / 10.f;
	    float num = cos(dijResult - (t / 7.f));
	    float den = dijResult + 1.f;
	    float div = num / den;
	    *ptrLevelGris = 128 + (127 * div);
//	    *ptrLevelGris = 128 + 127 * (cos(dijResult - t / 7.f) / (dijResult + 1.f));
	    }

	__device__
	float dij(int i, int j)
	    {
	    float fi = i - dim2 / 2.f;
	    float fj = j - dim2 / 2.f;
	    return (float) sqrt(fi * fi + fj * fj);
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Tools
	float dim2;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
