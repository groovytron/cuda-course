#include "LimitsTools.h"
#include "Indice1D.h"
#include <curand_kernel.h>

__global__ void setup_kernel_rand(curandState* tabDevGeneratorGM, int deviceId)
    {
    const int TID = Indice1D::tid();
    int deltaSeed = deviceId * INT_MAX / 10000;
    int deltaSequence = deviceId * 100;
    int deltaOffset = deviceId * 100;
    int seed = 1234 + deltaSeed;
    int sequenceNumber = TID + deltaSequence;
    int offset = deltaOffset;
    curand_init(seed, sequenceNumber, offset, &tabDevGeneratorGM[TID]);
    }
