#include <stdio.h>
#include <mpi.h>
#include<unistd.h>
int main(int argc, char *argv[]) {
    int rank, size;
    int data;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        if (rank == 0)
            printf("Please run with at least 2 processes.\n");
        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        data = 99;
        printf("Process 0 sleeping for 5 seconds before sending...\n");
        sleep(5);  // simulate some delay
        printf("Process 0 sending data: %d\n", data);
        MPI_Send(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process 0: Send completed!\n");
    }

    if (rank == 1) {
        printf("Process 1 waiting to receive data...\n");
        MPI_Recv(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received data: %d\n", data);

        // Operation after receive
        printf("Process 1 is now doing something AFTER receiving the message.\n");
    }

    MPI_Finalize();
    return 0;
}
