#pragma once

#include <math.h>
#include "MathTools.h"

#include "ColorTools_CPU.h"
using namespace cpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MandelbrotMath
    {
	/*--------------------------------------*\
	|*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	MandelbrotMath(uint w)
	    {
	    this->dim2 = w / 2;
	    }

	// constructeur copie: pas besoin car pas attribut ptr

	virtual ~MandelbrotMath(void)
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:

	void colorIJ(uchar4* ptrColorIJ, int i, int j, const int N)
	    {

	    uchar levelGris;
	    double x = 0;
	    double y = 0;

	    int k = f(x, y, N);
	    levelGris = k < N ? 0 : 1 / N * k;
//	    levelGris = 255;
	    ptrColorIJ->x = levelGris;
	    ptrColorIJ->y = levelGris;
	    ptrColorIJ->z = levelGris;

	    ptrColorIJ->w = 255; //opaque
	    }

    private:

	int f(int x, int y, const int N)
	    {
	    float a = 0;
	    float b = 0;
	    float aCopy = a;
	    int k = 0;
	    do
		{
		a = (a * a - b * b) + x;
		b = 2 * aCopy * b + y;
		k += 1;
		}
	    while (a * a + b * b < 2 && k < N);
	    }

	void dij(int i, int j, float* ptrResult)
	    {
	    //TODO cf fonction math pdf
	    float fi = i - dim2 / 2;
	    float fj = j - dim2 / 2;
	    *ptrResult = sqrt(fi * fi + fj * fj);
	    }

	/*--------------------------------------*\
	|*		Attribut			*|
	 \*-------------------------------------*/

    private:

	// Tools
	float dim2;

    }
;

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
