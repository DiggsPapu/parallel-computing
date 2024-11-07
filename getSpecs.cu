#include <cuda_runtime.h>
#include <stdio.h>

int main() {
    cudaDeviceProp props;
    cudaGetDeviceProperties(&props, 0); // Assuming device 0

    printf("Warp size: %d\n", props.warpSize);
    printf("Max threads per block: %d\n", props.maxThreadsPerBlock);
    printf("Max block dimensions (x, y, z): (%d, %d, %d)\n",
            props.maxThreadsDim[0], props.maxThreadsDim[1], props.maxThreadsDim[2]);
    printf("Max grid dimensions (x, y, z): (%d, %d, %d)\n",
            props.maxGridSize[0], props.maxGridSize[1], props.maxGridSize[2]);

    // Maximum size per grid dimension (x, y, z)
    int maxGridSizeX = props.maxGridSize[0];
    int maxGridSizeY = props.maxGridSize[1];
    int maxGridSizeZ = props.maxGridSize[2];

    // Maximum size per block dimension (x, y, z)
    int maxBlockSizeX = props.maxThreadsDim[0];
    int maxBlockSizeY = props.maxThreadsDim[1];
    int maxBlockSizeZ = props.maxThreadsDim[2];

    printf("Max grid size X: %d\n", maxGridSizeX);
    printf("Max grid size Y: %d\n", maxGridSizeY);
    printf("Max grid size Z: %d\n", maxGridSizeZ);

    printf("Max block size X: %d\n", maxBlockSizeX);
    printf("Max block size Y: %d\n", maxBlockSizeY);
    printf("Max block size Z: %d\n", maxBlockSizeZ);

    return 0;
}