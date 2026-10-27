
#ifndef IMAGE_H
#define IMAGE_H

typedef struct {
    int width;
    int height;
    int channels;
    unsigned char *data;
} Image;

int load_image(const char *filename, Image *img);
void free_image(Image *img);

void rgb_to_gray(const unsigned char *rgb,
                 unsigned char *gray,
                 int pixel_count);

int save_grayscale(const char *filename,
                   const unsigned char *gray,
                   int width,
                   int height);

int parallel_grayscale(const char *input_filename,
                       const char *output_filename);

#endif
