#include <iostream>
#include <assert.h>

#include "Device.h"
#include <assert.h>
#include "RayTracing.h"
#include "Sphere.h"
#include "SphereCreator.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void raytracing(Sphere* ptrDevSpheres, uchar4* ptrDevPixels, uint w, uint h, float t, int nbSpheres);

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

/*-------------------------*\
 |*	Constructeur	    *|
 \*-------------------------*/

RayTracing::RayTracing(const Grid& grid, uint w, uint h, float dt, int nbSpheres) :
	Animable_I<uchar4>(grid, w, h, "Raytracing_Cuda")
    {
    assert(w == h); // specific rippling

    // Inputs
    this->dt = dt;
    this->sizeOctet = nbSpheres * sizeof(Sphere);

    // Tools
    this->t = 0; // protected dans Animable

    this->nbSpheres = nbSpheres;
    const int BORD = 200;
    SphereCreator sphereCreator(nbSpheres, w, h, BORD);
    this->ptrSpheres = sphereCreator.getTabSphere();

    printf("Coucou from Host rayon: %f\n", ptrSpheres[0].getRayon());

    Device::malloc(&ptrDevSpheres, sizeOctet);
    Device::memclear(ptrDevSpheres, sizeOctet);
    Device::memcpyHToD(ptrDevSpheres, ptrSpheres, sizeOctet);

    }

RayTracing::~RayTracing()
    {
    // rien
    Device::free(ptrDevSpheres);
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 * Call periodicly by the API
 *
 * Note : domaineMath pas use car pas zoomable
 */
void RayTracing::process(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    Device::lastCudaError("rippling rgba uchar4 (before kernel)"); // facultatif, for debug only, remove for release

    // TODO lancer le kernel avec <<<dg,db>>>
    // le kernel est importer ci-dessus (ligne 19)

    raytracing <<<db, dg>>>(this->ptrDevSpheres, ptrDevPixels, w, h, t, this->nbSpheres);

    Device::lastCudaError("rippling rgba uchar4 (after kernel)"); // facultatif, for debug only, remove for release
    }

/**
 * Override
 * Call periodicly by the API
 */
void RayTracing::animationStep()
    {
    t += dt;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

