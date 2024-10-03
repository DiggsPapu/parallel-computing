#include <stdio.h>
#include <time.h>
#include <omp.h>

// Función recursiva de openmp para calcular Fibonacci
long long fib_recursive_omp(int n) {
    if (n <= 1) {
        return n;
    }

    long long x, y;

    #pragma omp task shared(x)
    x = fib_recursive_omp(n - 1);

    #pragma omp task shared(y)
    y = fib_recursive_omp(n - 2);

    #pragma omp taskwait
    return x + y;
}

// Función recursiva para calcular Fibonacci
long long fib_recursive(int n) {
    if (n <= 1) {
        return n;
    }
    return fib_recursive(n - 1) + fib_recursive(n - 2);
}

int main() {
    int n;
    long long result;
    clock_t start, end;
    double cpu_time_used;

    // Pedir al usuario que ingrese el valor de n
    printf("Ingrese un número para calcular Fibonacci: ");
    scanf("%d", &n);

    // Registrar el tiempo de inicio
    start = clock();
    result = fib_recursive(n);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    // Imprimir el resultado
    printf("Fibonacci de %d es: %lld\n", n, result);
    printf("Tiempo de ejecución: %f segundos\n", cpu_time_used);

    // Registrar el tiempo de inicio para la versión con OpenMP
    start = clock();
    #pragma omp parallel
    {
        #pragma omp single
        result = fib_recursive_omp(n);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Fibonacci de %d es: %lld (con OpenMP)\n", n, result);
    printf("Tiempo de ejecución (con OpenMP): %f segundos\n", cpu_time_used);


    return 0;
}
