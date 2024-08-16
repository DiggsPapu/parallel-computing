#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    double sum = 0.0;
    int n = 1;
    int thread_count = 1;

    if (argc > 1) {
        n = atoi(argv[1]);
        if (argc > 2) {
            thread_count = atoi(argv[2]);
        }
    }

    #pragma omp parallel for num_threads(thread_count) reduction(+:sum)
    for (int i = 0; i < n; i++) {
        double factor = (i % 2 == 0) ? 1.0 : -1.0;
        sum += factor / (2*i + 1);
    }
    
    double pi_aprox = 4.0 * sum;
    printf("Pi value: %lf \n", pi_aprox);

    return 0;
}
