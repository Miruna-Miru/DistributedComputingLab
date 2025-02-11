#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main() 
{
    int i, n = 10; // Reduce the size for better visibility in output
    int a[10], b[10], sum = 0; 

    // Initialize arrays
    for (i = 0; i < n; i++) {
        a[i] = i;
        b[i] = (i + 1); // Slight variation for better demonstration
    }

    printf("Array A: ");
    for (i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\nArray B: ");
    for (i = 0; i < n; i++) printf("%d ", b[i]);
    printf("\n");

    // Parallel sum reduction
    #pragma omp parallel for reduction(+:sum)
    for (i = 0; i < n; i++) {
        sum += a[i] * b[i];
        printf("Thread %d processing index %d: %d * %d = %d\n", omp_get_thread_num(), i, a[i], b[i], a[i] * b[i]);
    }

    // Print the final sum
    printf("Final Sum of element-wise product: %d\n", sum);
    return 0;
}
