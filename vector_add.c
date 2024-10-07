/* File: vector_add.c
*
* Purpose: Implement vector addition with large randomly generated vectors
*
* Compile: gcc -g -Wall -o vector_add vector_add.c
* Run: ./vector_add
*
* Input: None (vectors are generated randomly)
* Output: The first and last 10 elements of the vectors x, y, and the sum vector z = x+y
*
* Note:
* If the program detects an error (order of vector <= 0 or malloc
* failure), it prints a message and terminates.
*
* IPP: Section 3.4.6 (p. 109)
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define VECTOR_SIZE 95000000  // Minimum size of the vectors

void Allocate_vectors(double** x_pp, double** y_pp, double** z_pp, int n);
void Generate_random_vector(double a[], int n);
void Print_vector(double b[], int n, char title[]);
void Vector_sum(double x[], double y[], double z[], int n);

/*---------------------------------------------------------------------*/
int main(void) {
    int n = VECTOR_SIZE;
    double *x, *y, *z;
    clock_t start, end;
    double cpu_time_used;

    // Start measuring time for vector allocation and initialization
    start = clock();

    Allocate_vectors(&x, &y, &z, n);
    Generate_random_vector(x, n);
    Generate_random_vector(y, n);
    Vector_sum(x, y, z, n);

    // End measuring time for vector allocation and initialization
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    Print_vector(x, n, "Vector x:");
    Print_vector(y, n, "Vector y:");
    Print_vector(z, n, "The sum vector z:");
    printf("\nTook %f ms to run\n", (cpu_time_used) * 1000);
    free(x);
    free(y);
    free(z);
    return 0;
} /* main */

/*---------------------------------------------------------------------
* Function: Allocate_vectors
* Purpose: Allocate storage for the vectors
* In arg: n: the order of the vectors
* Out args: x_pp, y_pp, z_pp: pointers to storage for the vectors
*
* Errors: If one of the mallocs fails, the program terminates
*/
void Allocate_vectors(
    double** x_pp /* out */,
    double** y_pp /* out */,
    double** z_pp /* out */,
    int n /* in */) {
    *x_pp = malloc(n * sizeof(double));
    *y_pp = malloc(n * sizeof(double));
    *z_pp = malloc(n * sizeof(double));
    if (*x_pp == NULL || *y_pp == NULL || *z_pp == NULL) {
        fprintf(stderr, "Can't allocate vectors\n");
        exit(-1);
    }
} /* Allocate_vectors */

/*---------------------------------------------------------------------
* Function: Generate_random_vector
* Purpose: Fill a vector with random double values
* In arg: n: order of the vector
* Out arg: a: the vector to be filled
*/
void Generate_random_vector(
    double a[] /* out */,
    int n /* in */) {
    int i;
    srand(time(NULL));
    for (i = 0; i < n; i++)
        a[i] = (double)rand() / RAND_MAX * 100.0;  // Random values between 0 and 100
} /* Generate_random_vector */

/*---------------------------------------------------------------------
* Function: Print_vector
* Purpose: Print the first and last 10 elements of a vector
* In args: b: the vector to be printed
* n: the order of the vector
* title: title for print out
*/
void Print_vector(
    double b[] /* in */,
    int n /* in */,
    char title[] /* in */) {
    int i;
    printf("%s\n", title);
    printf("First 10 elements:\n");
    for (i = 0; i < 10; i++)
        printf("%f ", b[i]);
    printf("\nLast 10 elements:\n");
    for (i = n - 10; i < n; i++)
        printf("%f ", b[i]);
    printf("\n");
} /* Print_vector */

/*---------------------------------------------------------------------
* Function: Vector_sum
* Purpose: Add two vectors
* In args: x: the first vector to be added
* y: the second vector to be added
* n: the order of the vectors
* Out arg: z: the sum vector
*/
void Vector_sum(
    double x[] /* in */,
    double y[] /* in */,
    double z[] /* out */,
    int n /* in */) {
    int i;
    for (i = 0; i < n; i++)
        z[i] = x[i] + y[i];
} /* Vector_sum */
