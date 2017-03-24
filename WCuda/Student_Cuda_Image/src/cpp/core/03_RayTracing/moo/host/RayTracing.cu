#include <iostream>
#include <assert.h>

#include "Device.h"
#include <assert.h>
#include "RayTracing.h"

using std::cout;
using std::endl;

extern __global__ void rayTracing(uchar4* ptrDevPixels,uint w, uint h,float t,uint nbSphere, Sphere* ptrDevTabSphere);

RayTracing::RayTracing(uint nbSphere, const Grid& grid, uint w, uint h, float dt) :
	Animable_I<uchar4>(grid, w, h, "RayTracing_Cuda_RGBA_uchar4")
    {

    // Inputs
    this->dt = dt;
    this->nbSphere = nbSphere;
    this->sizeOctet = nbSphere * sizeof(Sphere);

    // Tools
    this->t = 0;
    this->dg = grid.dg;
    this->db = grid.db;

    SphereCreator sphereCreator(nbSphere, w, h, RayTracing::BORD);
    Sphere* ptrTabSpheres = sphereCreator.getTabSphere();

    Device::malloc(&ptrDevTabSphere, sizeOctet);
    Device::memclear(ptrDevTabSphere, sizeOctet);
    Device::memcpyHToD(ptrDevTabSphere, ptrTabSpheres, sizeOctet);
    }

RayTracing::~RayTracing()
    {
    Device::free(ptrDevTabSphere);
    }

void RayTracing::process(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
rayTracing<<<dg,db>>>(ptrDevPixels,w,h,t,nbSphere,ptrDevTabSphere);
//Device::synchronize();

}

void RayTracing::animationStep()
{
t += dt;
}

