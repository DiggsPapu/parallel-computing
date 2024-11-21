#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    // Inicializar el entorno MPI
    MPI_Init(&argc, &argv);

    // Obtener el número de procesos
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Obtener el rango de cada proceso
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Imprimir el mensaje desde cada proceso
    printf("Hello World, I'm process %d of %d!\n", world_rank, world_size);

    // Finalizar el entorno MPI
    MPI_Finalize();

    return 0;
}
