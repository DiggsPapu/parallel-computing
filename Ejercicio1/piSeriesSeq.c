#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char *argv[]) {
    double factor = 1.0;
    double sum = 0.0;
    int n;

     
    if (argc > 1) {
        n = atoi(argv[1]);
    }

    for (int k = 0; k < n; k++) {
        sum += factor/(2*k+1);
        factor = -factor;
    }
    double pi_aprox = 4.0 * sum;
    printf("Pi value: %lf \n",pi_aprox );

    return 0;
}