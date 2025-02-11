#include <omp.h>
#include <stdio.h>

int main()
{
    int x = 0;

    // Set the number of threads to 3
    #pragma omp parallel shared(x) num_threads(3)
    {
        #pragma omp critical
        x = x + 1;
    }  /* end of parallel section */

    // Print the final value of x
    printf("Final value of x: %d\n", x);
    
    return 0;
}
