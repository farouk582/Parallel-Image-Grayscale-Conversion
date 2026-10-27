
#include <stdio.h>
#include <mpi.h>
#include "image.h"

int parallel_grayscale(void);

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    parallel_grayscale();

    MPI_Finalize();
    return 0;
}
