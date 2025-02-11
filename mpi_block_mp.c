#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size, i;
    int buffer[10];
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Correcting the condition: Exit only when size < 2
    if (size < 2) {
        if (rank == 0) {  // Print only once to avoid duplicate messages
            printf("Please run with at least two processes.\n");
            fflush(stdout);
        }
        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        for (i = 0; i < 10; i++)
            buffer[i] = i;

        MPI_Send(buffer, 10, MPI_INT, 1, 123, MPI_COMM_WORLD);
        printf("Process 0 sent data to Process 1\n");
    } 
    else if (rank == 1) {  // Only process 1 receives
        for (i = 0; i < 10; i++)
            buffer[i] = -1;

        MPI_Recv(buffer, 10, MPI_INT, 0, 123, MPI_COMM_WORLD, &status);
        printf("Process 1 received data:\n");
        for (i = 0; i < 10; i++)
            printf("%d ", buffer[i]);
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}

