#include <mpi.h>
#include <stdio.h>
#include <math.h>

// Función para evaluar la función que queremos integrar
double f(double x) {
    return sin(x);  // Puedes cambiar esta función según sea necesario
}

int main(int argc, char** argv) {
    int rank, size;
    double a = 0.0, b = M_PI; // Intervalo de integración [a, b]
    int n = 1000000; // Número total de subintervalos
    double local_sum = 0.0, global_sum = 0.0;
    double h, local_a, local_b;
    int local_n;

    MPI_Init(&argc, &argv); // Inicializar el entorno MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtener el identificador del proceso
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtener el número de procesos

    // Paso 3: Definir los subintervalos
    h = (b - a) / n; // Tamaño de cada subintervalo
    local_n = n / size; // Subintervalos por proceso

    // Paso 4: Asignar subintervalos a cada proceso
    local_a = a + rank * local_n * h;
    local_b = local_a + local_n * h;

    // Paso 5: Calcular la suma de Riemann en el subintervalo local
    for (int i = 0; i < local_n; i++) {
        double x = local_a + i * h;
        local_sum += f(x) * h;
    }

    // Paso 7: Reducir y combinar las sumas parciales
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Paso 8: El proceso rank 0 imprime el resultado
    if (rank == 0) {
        printf("Resultado aproximado de la integral: %f\n", global_sum);
    }

    MPI_Finalize(); // Finalizar el entorno MPI
    return 0;
}
