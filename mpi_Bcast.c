#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size, i;

    // Initialize MPI
    MPI_Init(&argc, &argv);

    // Get the rank (process ID) of the current process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get the total number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Root process (rank 0) sets i = 27
    if (rank == 0) {
        i = 75;
        printf("Process %d (root) broadcasting i = %d\n", rank, i);
    }

    // Broadcast 'i' from process 0 to all other processes
    MPI_Bcast(&i, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process prints the received value
    printf("Process %d received i = %d\n", rank, i);

    // Synchronization barrier: Wait for all processes to reach this point
    MPI_Barrier(MPI_COMM_WORLD);

    // Finalize MPI
    MPI_Finalize();
    return 0;
}
