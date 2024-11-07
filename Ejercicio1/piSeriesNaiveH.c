#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <string.h>

int main(int argc, char *argv[]) {
    double factor = 1.0;
    double sum = 0.0;
    int n = 1;
    int thread_count = 1;
    int block_size = 16;
    char *schedule_type = "auto"; 

    if (argc > 1) {
        n = atoi(argv[1]);
        if (argc > 2) {
            thread_count = atoi(argv[2]);
            if (argc > 3) {
                block_size = atoi(argv[3]);
                if (argc > 3) {
                    schedule_type = argv[4];
                }
            }
        }
    }
    double start_time = omp_get_wtime();
    if (strcmp(schedule_type, "dynamic") == 0) {
        omp_set_schedule(omp_sched_dynamic, block_size);
    } else if (strcmp(schedule_type, "guided") == 0) {
        omp_set_schedule(omp_sched_guided, block_size);
    } else if (strcmp(schedule_type, "auto") == 0) {
        omp_set_schedule(omp_sched_auto, 0);
    } else if (strcmp(schedule_type, "static") == 0) {
        omp_set_schedule(omp_sched_static, 0);
    }
    #pragma omp parallel for num_threads(thread_count) private(factor) reduction(+:sum) schedule(runtime)
    for (int k = 0; k < n; k++) {
        factor = (k % 2 == 0) ? 1.0 : -1.0;
        sum += factor / (2*k + 1);
        factor = -factor;
    }
    
    double pi_aprox = 4.0 * sum;
    double end_time = omp_get_wtime();
    printf("Pi value: %lf \n", pi_aprox);
    printf("Time taken: %lf seconds\n", end_time - start_time);
    return 0;
}
