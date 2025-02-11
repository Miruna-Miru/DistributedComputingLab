#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int data[] = {1, 2, 3, 4, 5, 6, 7}; // Data array (size must be >= #processors)
    int rank, size, i = -1, j = -1;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Ensure there are no more processes than data elements
    if (size > 7) {
        if (rank == 0) {
            printf("Number of processes should not exceed %d\n", (int)(sizeof(data) / sizeof(data[0])));
        }
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) {
        printf("Root process is scattering data to all processes...\n");
    }

    // Scatter the data to all processes
    MPI_Scatter(data, 1, MPI_INT, &i, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("[%d] Received i = %d from scatter\n", rank, i);

    // Perform the reduction operation (product of all received values)
    printf("[%d] Participating in reduction operation with value %d\n", rank, i);
    MPI_Reduce(&i, &j, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);

    // Print the result only on the root process
    if (rank == 0) {
        printf("Root process received final reduced result j = %d\n", j);
    }

    MPI_Finalize();
    return 0;
}
