# cuda-course
A shameless cuda course's backup.

## TP Slice first ideas

```cuda
__global__ void slice(float* ptrDevGMResult, int nbSlice)
{
	extern __shared__ float tab [...
	reductionIntraThread(tabSM, nbSlice);
	__syncthreads();
        reductionAdd<...>(tabSM, ptrDevGMResult);
}
```
