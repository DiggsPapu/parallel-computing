#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 5000

int main(int argc, char** argv) {
    int rank, size;
    int *array = NULL;
    int local_sum = 0, total_sum = 0;
    int local_max, global_max;
    int local_min, global_min;
    float global_promedio;
    int array_size = ARRAY_SIZE;  // Cambiar a una variable
    int local_array_size;

    // Inicializar MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Comenzar a medir el tiempo
    double start_time = MPI_Wtime();  // Guardar el tiempo de inicio

    // El proceso maestro genera el array aleatorio
    if (rank == 0) {
        // Asignar memoria para el array y generar valores aleatorios
        array = (int*)malloc(array_size * sizeof(int));
        srand(time(NULL));  // Inicializar la semilla para la generación aleatoria
        printf("Array: [");
        for (int i = 0; i < array_size; i++) {
            array[i] = rand() % 1000;  // Generar valores enteros aleatorios entre 0 y 999
            printf("%d,", array[i]);
        }
        printf("]\n");
    }

    // Difundir el tamaño del array a todos los procesos
    MPI_Bcast(&array_size, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Calcular el tamaño del array que será distribuido a cada proceso
    local_array_size = array_size / size;

    int *local_array = (int*)malloc(local_array_size * sizeof(int));

    // Distribuir el array a los procesos usando Scatter
    MPI_Scatter(array, local_array_size, MPI_INT, local_array, local_array_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Inicializar valores locales de suma, max y min
    local_max = local_array[0];
    local_min = local_array[0];

    // Cada proceso calcula la suma, máximo y mínimo de su porción local
    for (int i = 0; i < local_array_size; i++) {
        int valor = local_array[i];
        local_sum += valor;

        if (valor > local_max) {
            local_max = valor;
        }
        if (valor < local_min) {
            local_min = valor;
        }
    }

    // Reducir la suma total en el proceso maestro usando Reduce
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Reducir el máximo global usando Reduce
    MPI_Reduce(&local_max, &global_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    // Reducir el mínimo global usando Reduce
    MPI_Reduce(&local_min, &global_min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

    // El proceso maestro calcula y muestra los resultados
    if (rank == 0) {
        global_promedio = (float)total_sum / array_size;
        printf("Suma: %d\n", total_sum);
        printf("Máximo: %d\n", global_max);
        printf("Mínimo: %d\n", global_min);
        printf("Promedio: %.2f\n", global_promedio);

        // Finalizar el tiempo y calcular la duración
        double end_time = MPI_Wtime();  // Guardar el tiempo de finalización
        double time_taken = end_time - start_time;  // Calcular el tiempo transcurrido

        // Mostrar el tiempo de ejecución
        printf("Tiempo de ejecución: %.6f segundos\n", time_taken);

        free(array);  // Liberar memoria del array en el proceso maestro
    }

    free(local_array);
    MPI_Finalize();

    return 0;
}
