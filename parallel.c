#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <mpi.h>
#include "image.h"

int parallel_grayscale(void)
{
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    Image img = {0, 0, 0, NULL};
    int width = 0, height = 0, pixel_count = 0;
    int loaded = 1;
    const char *outname = "output/grayscale.png";

    if (rank == 0)
    {
        char filename[1024];

        printf("Enter image path: ");
        fflush(stdout);

        if (fgets(filename, sizeof(filename), stdin) == NULL)
        {
            loaded = 0;
        }
        else
        {
            filename[strcspn(filename, "\r\n")] = '\0';

            if (!load_image(filename, &img))
            {
                loaded = 0;
            }
            else
            {
                long long n = (long long)img.width * img.height;

                if (n * 3 > INT_MAX)
                {
                    fprintf(stderr, "Image too large.\n");
                    free_image(&img);
                    loaded = 0;
                }
                else
                {
                    width = img.width;
                    height = img.height;
                    pixel_count = (int)n;
                }
            }
        }
    }

    MPI_Bcast(&loaded, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (!loaded)
        return 0;

    MPI_Bcast(&width, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&height, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&pixel_count, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int *counts = malloc(size * sizeof(int));
    int *displs = malloc(size * sizeof(int));
    int *rgb_counts = malloc(size * sizeof(int));
    int *rgb_displs = malloc(size * sizeof(int));

    if (!counts || !displs || !rgb_counts || !rgb_displs)
        MPI_Abort(MPI_COMM_WORLD, 1);

    int base = pixel_count / size;
    int remainder = pixel_count % size;
    int offset = 0;

    for (int i = 0; i < size; i++)
    {
        counts[i] = base + (i < remainder ? 1 : 0);
        displs[i] = offset;

        rgb_counts[i] = counts[i] * 3;
        rgb_displs[i] = offset * 3;

        offset += counts[i];
    }

    int local_pixels = counts[rank];

    unsigned char *local_rgb =
        malloc((size_t)(local_pixels > 0 ? local_pixels : 1) * 3);
    unsigned char *local_gray =
        malloc((size_t)(local_pixels > 0 ? local_pixels : 1));

    if (!local_rgb || !local_gray)
        MPI_Abort(MPI_COMM_WORLD, 1);

    unsigned char *gray = NULL;
    if (rank == 0)
    {
        gray = malloc((size_t)pixel_count);
        if (!gray)
            MPI_Abort(MPI_COMM_WORLD, 1);
    }

    MPI_Scatterv(
        rank == 0 ? img.data : NULL,
        rgb_counts, rgb_displs, MPI_UNSIGNED_CHAR,
        local_rgb, local_pixels * 3, MPI_UNSIGNED_CHAR,
        0, MPI_COMM_WORLD
    );

    rgb_to_gray(local_rgb, local_gray, local_pixels);

    MPI_Gatherv(
        local_gray, local_pixels, MPI_UNSIGNED_CHAR,
        gray, counts, displs, MPI_UNSIGNED_CHAR,
        0, MPI_COMM_WORLD
    );

    int saved = 1;

    if (rank == 0)
    {
        saved = save_grayscale(outname, gray, width, height);

        if (saved)
            printf("Grayscale image saved as %s\n", outname);
        else
            fprintf(stderr, "Error saving grayscale image.\n");

        free(gray);
        free_image(&img);
    }

    MPI_Bcast(&saved, 1, MPI_INT, 0, MPI_COMM_WORLD);

    free(local_rgb);
    free(local_gray);
    free(counts);
    free(displs);
    free(rgb_counts);
    free(rgb_displs);

    return saved;
}