#pragma once

#include <cudaTools.h>
#include <ColorTools_GPU.h>
#include <math.h>

#include "../../Sphere.h"

class Sphere;

using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RayTracingMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ RayTracingMath(int w, int h, Sphere* ptrDevSpheres, int nbSpheres)
	    {
	    this->dim2 = w / 2;
	    this->ptrDevSpheres = ptrDevSpheres;
	    this->nbSpheres = nbSpheres;
	    if (Indice2D::tid() == 0)
		{
		printf("Coucou from device ");
		printf("nb sphere: %d ", this->nbSpheres);
		printf("rayon: %f\n", ptrDevSpheres[0].getRayon());
		}

	    }

	// constructeur copie automatique car pas pointeur dans VagueMath

	__device__
	                                                          virtual ~RayTracingMath()
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
	    uchar levelGris = 128;

	    float hue = f(i, j, t); // update levelGris
//
	    ColorTools::HSB_TO_RVB(hue, ptrColor);
	    levelGris = 0;
//
//	    ptrColor->x = levelGris;
//	    ptrColor->y = levelGris;
//	    ptrColor->z = levelGris;

	    ptrColor->w = 255; // opaque
	    }

    private:

	__device__
	float f(int i, int j, float t)
	    {
	    //	Calculer h 2
	    //	Calculer isEndessous
	    //	Calculer dz
	    //	Calculer distance
	    //	Calculer brightnesse
	    for (int k = 0; k < this->nbSpheres; k++)
		{
		Sphere sphere = ptrDevSpheres[k];
		float hCarre = sphere.hCarre((float) j, (float) i);
//		float isEndessous = sphere.isEnDessous(hCarre);
//		float dz = sphere.dz(hCarre);
//		float distance = sphere.distance(dz);
//		float hue = 1;

		if (sphere.isEnDessous(hCarre))
		    {
		    return 0.5f;
		    }

		}

	    return 0.25f;
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Tools
	float dim2;
	Sphere* ptrDevSpheres;
	int nbSpheres;
    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
