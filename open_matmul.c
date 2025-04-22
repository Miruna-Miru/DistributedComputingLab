#include<stdio.h>
#include<omp.h>

#define n 3

void main()
{
    omp_set_num_threads(3);
     int a[n][n],b[n][n],c[n][n];
     int i,j,k;
     for( i=0;i<n;i++)
     {
        for( j=0;j<n;j++)
        {
            a[i][j]=1;
            b[i][j]=1;
            c[i][j]=0;
        }
     }

     #pragma omp parallel for private(i,j,k) shared(a,b,c)
     for(i=0;i<n;i++)
     {
        printf("Performing by : %d",omp_get_thread_num());
     for(j=0;j<n;j++)
     {
     for(k=0;k<n;k++)
       c[i][j]+=a[i][k]*b[k][j];
     }
    }
   printf("C : ");
    for( i=0;i<n;i++)
     {
        for( j=0;j<n;j++)
        {
            printf("%d ",c[i][j]);
        }
        printf("\n");
     }

}