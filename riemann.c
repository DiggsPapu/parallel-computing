#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float trapezoides(int a, int b){
    float n = pow(10, 6);
    float h = (b-a)/n;
    float result = 0.0;
    for (int i = 0; i < n; i++){
        float Xi = a + i * h; 
        // En caso de f(x) = x^2
        // result += pow(Xi,2);
        // En caso de 2x^3
        result += 2*pow(Xi, 3);
        // En caso de sin(x)
        result += sin(Xi);
        if (n-1 == i){
            // En caso de f(x) = x^2
            // result += pow(b,2);
            // En caso de 2x^3
            result += 2*pow(b, 3);
            // En caso de sin(x)
            // result += sin(b);
        }
    }
    result = result * h;
    return result;
}

int main(int argc, char *argv[]) {
    int a = 10;
    int b = 10;
    // in case argument passed is something
    if (argc > 1) {
        a = atoi(argv[1]);
        b = atoi(argv[2]);
    };
    printf("resultado : %f\n", trapezoides(a, b));
    return 0;
}