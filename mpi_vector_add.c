/* File: mpi_vector_add.c
 *
 * Purpose: Implement parallel vector addition using a block
 * distribution of the vectors. This version also
 * illustrates the use of MPI_Scatter and MPI_Gather.
 *
 * Compile: mpicc -g -Wall -o mpi_vector_add mpi_vector_add.c
 * Run: mpiexec -n <comm_sz> ./vector_add
 *
 * Input: The order of the vectors, n, and the vectors x and y
 * Output: The sum vector z = x+y
 *
 * Notes:
 * 1. The order of the vectors, n, should be evenly divisible
 * by comm_sz
 * 2. DEBUG compile flag.
 * 3. This program does fairly extensive error checking. When
 * an error is detected, a message is printed and the processes
 * quit. Errors detected are incorrect values of the vector
 * order (negative or not evenly divisible by comm_sz), and
 * malloc failures.
 *
 * IPP: Section 3.4.6 (pp. 109 and ff.)
 */
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

void Check_for_error(int local_ok, char fname[], char message[], MPI_Comm comm);
void Read_n(int* n_p, int* local_n_p, int my_rank, int comm_sz, MPI_Comm comm);
void Allocate_vectors(double** local_x_pp, double** local_y_pp, double** local_z_pp, int local_n, MPI_Comm comm);
void Generate_random_vector(double local_a[], int local_n, int n, int my_rank, MPI_Comm comm);
void Print_vector(double local_b[], int local_n, int n, char title[], int my_rank, MPI_Comm comm);
void Parallel_vector_sum(double local_x[], double local_y[], double local_z[], int local_n);
double Dot_product(double local_x[], double local_y[], int local_n);
void Scalar_multiply(double local_a[], double local_b[], double scalar, int local_n);

/*-------------------------------------------------------------------*/
int main(void) {
    int n = 95000000; // Minimum of 100,000 elements as required
    int local_n;
    int comm_sz, my_rank;
    double *local_x, *local_y, *local_z;
    MPI_Comm comm;
    double scalar = 3.0;
    double tstart, tend;

    MPI_Init(NULL, NULL);
    comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm, &comm_sz);
    MPI_Comm_rank(comm, &my_rank);

    local_n = n / comm_sz; // Calculate local size of each vector
    tstart = MPI_Wtime();

    Allocate_vectors(&local_x, &local_y, &local_z, local_n, comm);
    Generate_random_vector(local_x, local_n, n, my_rank, comm);
    Generate_random_vector(local_y, local_n, n, my_rank, comm);

    Parallel_vector_sum(local_x, local_y, local_z, local_n);
    
    // Calcular producto punto
    double local_dot = Dot_product(local_x, local_y, local_n);
    double global_dot;
    MPI_Reduce(&local_dot, &global_dot, 1, MPI_DOUBLE, MPI_SUM, 0, comm);

    // Calcular el producto escalar
    Scalar_multiply(local_x, local_x, scalar, local_n); // Multiplicando x por escalar
    Scalar_multiply(local_y, local_y, scalar, local_n); // Multiplicando y por escalar

    tend = MPI_Wtime();

    Print_vector(local_x, local_n, n, "Vector x", my_rank, comm);
    Print_vector(local_y, local_n, n, "Vector y", my_rank, comm);
    Print_vector(local_z, local_n, n, "Resultant vector z = x + y", my_rank, comm);

    if (my_rank == 0) {
        printf("\nProducto punto total: %f\n", global_dot);
        printf("\nTook %f ms to run\n", (tend - tstart) * 1000);
    }

    free(local_x);
    free(local_y);
    free(local_z);
    MPI_Finalize();
    return 0;
} /* main */

/*-------------------------------------------------------------------
 * Function: Check_for_error
 * Purpose: Check whether any process has found an error.
 */
void Check_for_error(int local_ok, char fname[], char message[], MPI_Comm comm) {
    int ok;
    MPI_Allreduce(&local_ok, &ok, 1, MPI_INT, MPI_MIN, comm);
    if (ok == 0) {
        int my_rank;
        MPI_Comm_rank(comm, &my_rank);
        if (my_rank == 0) {
            fprintf(stderr, "Proc %d > In %s, %s\n", my_rank, fname, message);
            fflush(stderr);
        }
        MPI_Finalize();
        exit(-1);
    }
}

/*-------------------------------------------------------------------
 * Function: Allocate_vectors
 * Purpose: Allocate storage for x, y, and z.
 */
void Allocate_vectors(double** local_x_pp, double** local_y_pp, double** local_z_pp, int local_n, MPI_Comm comm) {
    int local_ok = 1;
    char* fname = "Allocate_vectors";
    *local_x_pp = malloc(local_n * sizeof(double));
    *local_y_pp = malloc(local_n * sizeof(double));
    *local_z_pp = malloc(local_n * sizeof(double));
    if (*local_x_pp == NULL || *local_y_pp == NULL || *local_z_pp == NULL) local_ok = 0;
    Check_for_error(local_ok, fname, "Can't allocate local vector(s)", comm);
}

/*-------------------------------------------------------------------
 * Function: Generate_random_vector
 * Purpose: Generate a vector with random values distributed among processes.
 */
void Generate_random_vector(double local_a[], int local_n, int n, int my_rank, MPI_Comm comm) {
    double* a = NULL;
    int i;
    int local_ok = 1;
    char* fname = "Generate_random_vector";

    if (my_rank == 0) {
        a = malloc(n * sizeof(double));
        if (a == NULL) local_ok = 0;
        Check_for_error(local_ok, fname, "Can't allocate temporary vector", comm);

        srand(time(NULL)); // Seed random number generator
        for (i = 0; i < n; i++)
            a[i] = (double)rand() / RAND_MAX; // Generate random numbers between 0 and 1

        MPI_Scatter(a, local_n, MPI_DOUBLE, local_a, local_n, MPI_DOUBLE, 0, comm);
        free(a);
    } else {
        Check_for_error(local_ok, fname, "Can't allocate temporary vector", comm);
        MPI_Scatter(a, local_n, MPI_DOUBLE, local_a, local_n, MPI_DOUBLE, 0, comm);
    }
}

/*-------------------------------------------------------------------
 * Function: Print_vector
 * Purpose: Print the first and last 10 elements of a vector.
 */
void Print_vector(double local_b[], int local_n, int n, char title[], int my_rank, MPI_Comm comm) {
    double* b = NULL;
    int i;
    int local_ok = 1;
    char* fname = "Print_vector";

    if (my_rank == 0) {
        b = malloc(n * sizeof(double));
        if (b == NULL) local_ok = 0;
        Check_for_error(local_ok, fname, "Can't allocate temporary vector", comm);

        MPI_Gather(local_b, local_n, MPI_DOUBLE, b, local_n, MPI_DOUBLE, 0, comm);

        printf("%s\n", title);
        printf("First 10 elements: ");
        for (i = 0; i < 10; i++)
            printf("%f ", b[i]);
        printf("\nLast 10 elements: ");
        for (i = n - 10; i < n; i++)
            printf("%f ", b[i]);
        printf("\n");

        free(b);
    } else {
        Check_for_error(local_ok, fname, "Can't allocate temporary vector", comm);
        MPI_Gather(local_b, local_n, MPI_DOUBLE, b, local_n, MPI_DOUBLE, 0, comm);
    }
}

/*-------------------------------------------------------------------
 * Function: Parallel_vector_sum
 * Purpose: Add two vectors that have been distributed among the processes.
 */
void Parallel_vector_sum(double local_x[], double local_y[], double local_z[], int local_n) {
    int local_i;
    for (local_i = 0; local_i < local_n; local_i++)
        local_z[local_i] = local_x[local_i] + local_y[local_i];
} /* Parallel_vector_sum */

/*-------------------------------------------------------------------
 * Function: Dot_product
 * Purpose: Calculate the dot product of two local vectors.
 */
double Dot_product(double local_x[], double local_y[], int local_n) {
    double local_sum = 0.0;
    for (int i = 0; i < local_n; i++)
        local_sum += local_x[i] * local_y[i];
    return local_sum;
}

/*-------------------------------------------------------------------
 * Function: Scalar_multiply
 * Purpose: Multiply a vector by a scalar.
 */
void Scalar_multiply(double local_a[], double local_b[], double scalar, int local_n) {
    for (int i = 0; i < local_n; i++)
        local_b[i] = local_a[i] * scalar;
}