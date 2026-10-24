
#ifndef IMAGE_H
#define IMAGE_H

#include <mpi.h>
#include <stddef.h>

// Image stored as RGB bytes.
typedef struct {
    int width;
    int height;
    int channels;
    unsigned char *data;
} Image;

// image_io.c
int load_image(const char *filename, Image *img);
void free_image(Image *img);

// grayscale.c
void rgb_to_gray(const unsigned char *rgb,
                 unsigned char *gray,
                 int pixel_count);

// parallel.c
unsigned char *parallel_grayscale(
    const unsigned char *rgb_on_root,
    int width,
    int height,
    MPI_Comm comm
);

// image_output.c
int save_grayscale(const char *filename,
                   const unsigned char *gray,
                   int width,
                   int height);

#endif

