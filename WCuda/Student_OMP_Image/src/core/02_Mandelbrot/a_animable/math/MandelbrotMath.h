#pragma once

#include <cudaType_CPU.h>
#include <Calibreur_CPU.h>
#include <ColorTools_CPU.h>
#include <Interval_CPU.h>
#include <math.h>

#include <stdio.h>

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
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	MandelbrotMath(uint n) :
		calibreur(Interval<float>(0, n), Interval<float>(0, 1))
	    {
	    this->n = n;
	    }

	virtual ~MandelbrotMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	void colorXY(uchar4* ptrColor, float x, float y)
	    {
//	    printf("x = %f", x);
//	    printf("y = %f", y);
	    float z = (float) f(x, y);
	    if (z == this->n)
		{
		ptrColor->x = 0;
		ptrColor->y = 0;
		ptrColor->z = 0;
		}
	    else
		{
		calibreur.calibrer(z);
		float hue = z;
		ColorTools::HSB_TO_RVB(hue, ptrColor); // update color

		}
	    ptrColor->w = 255; // opaque
	    }

    private:

	int f(float x, float y)
	    {
	    float a = 0;
	    float b = 0;
	    float aCopy;
	    int k = 0;

	    do
		{
		aCopy = a;
		a = (a * a - b * b) + x;
		b = 2.0f * aCopy * b + y;
		k += 1;
		}
	    while (a * a + b * b < 4.0f && k < this->n);

	    return k;
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Input
	uint n;

	// Tools
	Calibreur<float> calibreur;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
