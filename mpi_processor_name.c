#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    char name[MPI_MAX_PROCESSOR_NAME];
    int resultlen;

    MPI_Init(&argc, &argv);

    MPI_Get_processor_name(name, &resultlen);

    printf("Running on processor: %s (length = %d)\n", name, resultlen);

    MPI_Finalize();
    return 0;
}
