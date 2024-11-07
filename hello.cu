/*
 ============================================================================
 Author        : G. Barlas
 Version       : 1.0
 Last modified : December 2014
 License       : Released under the GNU GPL 3.0
 Description   :
 To build use  : nvcc hello.cu -o hello -arch=sm_20
 ============================================================================
 */
#include <stdio.h>
#include <cuda.h>

__global__ void hello()
{
  // Print a message only for the last thread (1023) of each block
  // Thread id in a block
  if (threadIdx.x == 1023)
  {
     printf("Hello world from thread %d, block %d\n", threadIdx.x, blockIdx.x);
     printf("Name: Diego Alonzo, Carne: 20172\n");
  }
}

int main()
{
  // 2 blocks of 1024 threads each
  hello<<<2,1024>>>();
  cudaThreadSynchronize(); //deprecated
  return 0;
}
