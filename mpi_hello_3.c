#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    // Inicializar el entorno MPI
    MPI_Init(&argc, &argv);

    // Obtener el número de procesos
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Obtener el rango de cada proceso
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Buffer para el mensaje
    char message[100];

    if (world_rank != 0) {
        // Todos los procesos, excepto el proceso 0, envían un mensaje
        sprintf(message, "Hello from process %d", world_rank);
        printf("Process %d: Sending message to process 0.\n", world_rank);
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);

        // Recibir confirmación del proceso 0
        MPI_Recv(message, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d: Received confirmation from process 0: '%s'\n", world_rank, message);
    } else {
        // El proceso 0 recibe los mensajes de todos los demás procesos
        for (int i = 1; i < world_size; i++) {
            MPI_Recv(message, 100, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Process 0: Received message '%s' from process %d.\n", message, i);

            // Enviar confirmación de recepción
            sprintf(message, "Message received by process 0 from process %d", i);
            MPI_Send(message, strlen(message) + 1, MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
    }

    // Finalizar el entorno MPI
    MPI_Finalize();

    return 0;
}
