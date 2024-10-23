#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Función para evaluar la función que queremos integrar
double f(double x) {
    return 2 * pow(x, 3); // 2x^3
    // return pow(x, 2); // x^2
    // return sin(x);  // sin(x)
}

int main(int argc, char** argv) {
    int rank, size;
    double a, b; // Intervalo de integración [a, b]
    int n = 1000000; // Número total de subintervalos
    double local_sum = 0.0, global_sum = 0.0;
    double h, local_a, local_b;
    int local_n;

    // Leer argumentos de línea de comandos
    if (argc < 3) {
        if (rank == 0) {
            fprintf(stderr, "Uso: %s <a> <b>\n", argv[0]);
        }
        MPI_Finalize();
        return -1;
    }

    a = atof(argv[1]);
    b = atof(argv[2]);

    MPI_Init(&argc, &argv); // Inicializar el entorno MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtener el identificador del proceso
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtener el número de procesos

    // Definir los subintervalos
    h = (b - a) / n; // Tamaño de cada subintervalo
    local_n = n / size; // Subintervalos por proceso

    // Asignar subintervalos a cada proceso
    local_a = a + rank * local_n * h;
    local_b = local_a + local_n * h;

    // Calcular la suma de Riemann en el subintervalo local
    for (int i = 0; i < local_n; i++) {
        double x = local_a + i * h;
        local_sum += f(x) * h;
    }

    // Reducir y combinar las sumas parciales
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // El proceso rank 0 imprime el resultado
    if (rank == 0) {
        printf("Resultado aproximado de la integral en el rango [%f, %f]: %f\n", a, b, global_sum);
    }

    MPI_Finalize(); // Finalizar el entorno MPI
    return 0;
}
