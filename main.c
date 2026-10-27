
#include <stdio.h>
#include <mpi.h>
#include "image.h"

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (argc != 3)
    {
        if (rank == 0)
        {
            printf("Usage: %s <input_image> <output_image>\n",
                   argv[0]);
        }

        MPI_Finalize();
        return 1;
    }

    int result = parallel_grayscale(argv[1], argv[2]);

    MPI_Finalize();

    return result ? 0 : 1;
}
