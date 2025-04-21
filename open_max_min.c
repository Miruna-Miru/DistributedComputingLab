#include <omp.h>
#include <stdio.h>
#include <limits.h>  // For INT_MIN and INT_MAX

int main() {
    int n;
    printf("Enter number of elements:\n");
    scanf("%d", &n);

    int arr[n];
    printf("Enter elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    omp_set_num_threads(5);

   
    int max = INT_MIN;
    int min = INT_MAX;

    #pragma omp parallel for  reduction(max:max) reduction(min:min)
    for (int i = 0; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
        if (arr[i] < min)
            min = arr[i];
    }

   
    printf("Maximum value: %d\n", max);
    printf("Minimum value: %d\n", min);

    return 0;
}
