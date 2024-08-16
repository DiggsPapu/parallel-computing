#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(int argc, char *argv[]) {
    double factor = 1.0;
    double sum = 0.0;
    int n;

     
    if (argc > 1) {
        n = atoi(argv[1]);
    }
    clock_t start_time = clock();
    for (int k = 0; k < n; k++) {
        sum += factor/(2*k+1);
        factor = -factor;
    }
    double pi_aprox = 4.0 * sum;
    clock_t end_time = clock();
    double time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Pi value: %lf \n",pi_aprox );
    printf("Time taken: %lf seconds\n", time_spent);

    return 0;
}