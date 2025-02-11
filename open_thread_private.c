#include <stdio.h>
#include <omp.h>

int counter;  // Global variable
#pragma omp threadprivate(counter)  // Each thread gets its own copy

int main() {
    // First Parallel Region
    printf("First Parallel Region:\n");
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        counter = tid * 10; // Initialize counter differently for each thread
        printf("Thread %d: counter = %d\n", tid, counter);
    } // End of first parallel region

    printf("************************************\n");
    printf("Serial Section: Only the master thread executes this.\n");
    printf("************************************\n");

    // Second Parallel Region
    printf("Second Parallel Region:\n");
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        printf("Thread %d: counter = %d\n", tid, counter);  // Retains values from the first parallel region
    } // End of second parallel region

    return 0;
}
