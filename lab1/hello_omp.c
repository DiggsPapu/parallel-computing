#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int numThreads = 10;
    // in case argument passed is something
    if (argc > 1) {
        numThreads = atoi(argv[1]);
    };
    // Set the num of threads
    omp_set_num_threads(numThreads);
    // Parallel section
    #pragma omp parallel
    {
        int threadId = omp_get_thread_num();
        int totalThreads = omp_get_num_threads();
        printf("Hello from thread %d of %d!\n", threadId, totalThreads);
    }

    return 0;
}
