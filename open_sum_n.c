#include <stdio.h>
#include <omp.h>

int main()  // Always use `int main()` instead of `void main()`
{
    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    int sum = 0;
    omp_set_num_threads(3);

    #pragma omp parallel for reduction(+:sum)
    for(int i = 1; i <= n; i++)
    {
        printf("Performing by Thread %d\n", omp_get_thread_num());
        sum += i;
    }

    printf("Final value is: %d\n", sum);
    return 0;
}
