/*

        		//No output chat code
#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    int myid, numprocs, left, right;
    int buffer[10], buffer2[10];
    MPI_Request request, request2;
    MPI_Status status1, status2;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    right = (myid + 1) % numprocs;
    left = myid - 1;
    if (left < 0)
        left = numprocs - 1;

    // Initialize buffer2 before sending
    for (int i = 0; i < 10; i++)
        buffer2[i] = myid;

    MPI_Irecv(buffer, 10, MPI_INT, left, 123, MPI_COMM_WORLD, &request);
    MPI_Isend(buffer2, 10, MPI_INT, right, 123, MPI_COMM_WORLD, &request2);

    MPI_Wait(&request, &status1);
    MPI_Wait(&request2, &status2);

    // Optional: Synchronize processes
    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Finalize();
    return 0;
}

*/



/*
                        //mam's code
 #include "mpi.h"
 #include <stdio.h>
 int main(int argc, char *argv[])
 {
    int myid, numprocs, left, right;
    int buffer[10], buffer2[10];
    MPI_Request request, request2;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
 MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    right = (myid + 1) % numprocs;
    left = myid - 1;
    if (left < 0)
        left = numprocs - 1;
 MPI_Irecv(buffer, 10, MPI_INT, left, 123, MPI_COMM_WORLD, &request);
    MPI_Isend(buffer2, 10, MPI_INT, right, 123, MPI_COMM_WORLD, &request2);
 MPI_Wait(&request, &status);
 MPI_Wait(&request2, &status);
 MPI_Finalize();
    return 0;
 }
*/




			//output readable code
#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    int myid, numprocs, left, right;
    int buffer[10], buffer2[10];
    MPI_Request request, request2;
    MPI_Status status1, status2;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    right = (myid + 1) % numprocs;
    left = myid - 1;
    if (left < 0)
        left = numprocs - 1;

    // Initialize buffer2 with process ID for tracking
    for (int i = 0; i < 10; i++)
        buffer2[i] = myid;

    printf("Process %d: Preparing to send data to Process %d\n", myid, right);
    printf("Process %d: Expecting to receive data from Process %d\n", myid, left);

    MPI_Irecv(buffer, 10, MPI_INT, left, 123, MPI_COMM_WORLD, &request);
    MPI_Isend(buffer2, 10, MPI_INT, right, 123, MPI_COMM_WORLD, &request2);

    MPI_Wait(&request, &status1);
    printf("Process %d: Received data from Process %d\n", myid, left);

    MPI_Wait(&request2, &status2);
    printf("Process %d: Successfully sent data to Process %d\n", myid, right);

    // Synchronize output for better readability
 //   MPI_Barrier(MPI_COMM_WORLD);

    printf("Process %d: Communication complete.\n", myid);

    MPI_Finalize();
    return 0;
}
