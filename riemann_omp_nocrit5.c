#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

float trapezoides(int a, int b, int num_threads) {
    float n = pow(10, 6);
    float h = (b - a) / n;
    float global_result = 0.0;
    float* results = (float*)malloc(num_threads * sizeof(float));  // Arreglo para almacenar resultados locales

    int n_local = n / num_threads;

    #pragma omp parallel num_threads(num_threads)
    {
        int thread_id = omp_get_thread_num();
        float a_local = a + thread_id * n_local * h;
        float b_local = a_local + n_local * h;
        float local_result = 0.0;

        for (int i = 0; i < n_local; i++) {
            float Xi = a_local + i * h;
            // En caso de f(x) = x^2
            // local_result += pow(Xi,2);
            // En caso de 2x^3
            local_result += 2*pow(Xi, 3);
            // En caso de sin(x)
            // local_result += sin(Xi);
            if (i == n_local - 1) {
                // En caso de f(x) = x^2
                // local_result += pow(b_local,2);
                // En caso de 2x^3
                local_result += 2*pow(b_local, 3);
                // En caso de sin(x)
                // local_result += sin(b_local);
            }
        }

        local_result *= h;
        results[thread_id] = local_result;  // Guardar resultado local en el arreglo
    }

    // Sumar los resultados locales
    for (int i = 0; i < num_threads; i++) {
        global_result += results[i];
    }

    free(results);  // Liberar memoria
    return global_result;
}

int main(int argc, char *argv[]) {
    int a = 0;
    int b = 100;
    int num_threads = 4;

    if (argc > 1) {
        a = atoi(argv[1]);
        b = atoi(argv[2]);
        if (argc > 3) {
            num_threads = atoi(argv[3]);
        }
    }

    printf("Resultado: %f\n", trapezoides(a, b, num_threads));

    return 0;
}