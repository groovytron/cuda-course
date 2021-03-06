#include <curand_kernel.h>
#include <limits.h>
#include <Indice1D.h>

// Each thread gets same seed, a different sequence number
// no offset
__global__
void setup_kernel_rand(curandState* tabDevGenerator, int deviceId)
    {
    // Customisation du generator:
    // Proposition, au lecteur de faire mieux !
    // Contrainte : Doit etre différent d'un GPU à l'autre
    // Contrainte : Doit etre différent d’un thread à l’autre
    const int TID = Indice1D::tid();
    int deltaSeed = deviceId * INT_MAX / 10000;
    int deltaSequence = deviceId * 100;
    int deltaOffset = deviceId * 100;
    int seed = 1234 + deltaSeed;
    int sequenceNumber = TID + deltaSequence;
    int offset = deltaOffset;
    curand_init(seed, sequenceNumber, offset, &tabDevGenerator[TID]);
    }
