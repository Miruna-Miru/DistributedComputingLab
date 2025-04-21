#include <omp.h>
#include <stdio.h>

int main()
{
    int n, nthreads;
    printf("Enter no of threads (max 7) : ");
    scanf("%d", &nthreads);
    printf("Enter the nth term : ");
    scanf("%d", &n);

    omp_set_num_threads(nthreads);

    #pragma omp parallel for
    for (int i = 2; i < n; i++) // Start from 2 (1 is not prime)
    {
        int flag = 0;
        for (int j = 2; j * j <= i; j++)
        {
            if (i % j == 0)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
            printf("Prime is : %d and by thread %d \n", i, omp_get_thread_num());
    }

    return 0;
}
