#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    double factor = 1.0;
    double sum = 0.0;
    int n = 1;
    int thread_count = 1;

    if (argc > 1) {
        n = atoi(argv[1]);
        if (argc > 2) {
            thread_count = atoi(argv[2]);
        }
    }
    double start_time = omp_get_wtime();
    #pragma omp parallel for num_threads(thread_count) private(factor) reduction(+:sum)
    for (int k = 0; k < n; k++) {
        factor = (k % 2 == 0) ? 1.0 : -1.0;
        sum += factor / (2*k + 1);
        factor = -factor;
    }
    
    double pi_aprox = 4.0 * sum;
    double end_time = omp_get_wtime();
    printf("Pi value: %lf \n", pi_aprox);
    printf("Time taken: %lf seconds\n", end_time - start_time);
    return 0;
}
