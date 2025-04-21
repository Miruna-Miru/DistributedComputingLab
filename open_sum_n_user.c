#include<omp.h>
#include<stdio.h>

void main()
{
    int n;
    printf("Enter no of elements : ");
    scanf("%d",&n);
    int arr[n];
    printf("Enter elements : ");
    for(int i=0;i<n;i++)
      scanf("%d",&arr[i]);
    omp_set_num_threads(5);
    int sum=0;
    #pragma omp parallel for reduction(+:sum)
    for(int i=0;i<n;i++)
      sum+=arr[i];
    printf("Final sum is : %d",sum);
}