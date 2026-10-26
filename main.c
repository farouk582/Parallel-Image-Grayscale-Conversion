#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include "image.h"

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        char filename[1024];
        Image img;
        printf("Enter image path: ");
        fflush(stdout);

        if (fgets(filename, sizeof(filename), stdin) == NULL)
        {
            fprintf(stderr, "Error reading image path.\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        // Remove the newline
        filename[strcspn(filename, "\n")] = '\0';

        if (!load_image(filename, &img))
        {
            fprintf(stderr, "Failed to load image.\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        printf("Image loaded successfully in main!\n");
        free_image(&img);
    }

    MPI_Finalize();
    return 0;
}
