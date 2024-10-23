#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>  // Para medir el tiempo de ejecución

float trapezoides(int a, int b) {
    float n = pow(10, 6);
    float h = (b - a) / n;
    float result = 0.0;
    for (int i = 0; i < n; i++) {
        float Xi = a + i * h; 
        // En caso de f(x) = x^2
        // result += pow(Xi, 2);
        // En caso de 2x^3
        result += 2 * pow(Xi, 3);
        // En caso de sin(x)
        result += sin(Xi);
        if (n - 1 == i) {
            // En caso de f(x) = x^2
            // result += pow(b, 2);
            // En caso de 2x^3
            result += 2 * pow(b, 3);
            // En caso de sin(x)
            // result += sin(b);
        }
    }
    result = result * h;
    return result;
}

int main(int argc, char *argv[]) {
    int a = 0;
    int b = 100;
    // En caso de pasar argumentos
    if (argc > 1) {
        a = atoi(argv[1]);
        b = atoi(argv[2]);
    }

    // Medir el tiempo de inicio
    clock_t start_time = clock();

    // Calcular el resultado
    float result = trapezoides(a, b);

    // Medir el tiempo de fin
    clock_t end_time = clock();

    // Calcular el tiempo de ejecución
    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Imprimir resultado y tiempo de ejecución
    printf("Resultado: %f\n", result);
    printf("Tiempo de ejecución: %f segundos\n", execution_time);

    return 0;
}
