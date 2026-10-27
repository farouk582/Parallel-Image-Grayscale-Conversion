
#include <stdio.h>
#include <stdlib.h>
#include "image.h"

int main(void)
{
    Image img = {0};

    /* 1. Load the original image */
    if (!load_image("input2.jpg", &img)) {
        return 1;
    }

    /* 2. Calculate the number of pixels */
    int pixel_count = img.width * img.height;

    /* 3. Allocate memory for grayscale pixels */
    unsigned char *gray =
        malloc((size_t)pixel_count * sizeof(unsigned char));

    if (gray == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        free_image(&img);
        return 1;
    }

    /* 4. Convert RGB to grayscale */
    rgb_to_gray(img.data, gray, pixel_count);

    /* 5. Save the grayscale image */
    if (save_grayscale("output_gray2.png", gray,
                       img.width, img.height)) {
        printf("Grayscale image saved: output_gray.png\n");
    } else {
        fprintf(stderr, "Failed to save grayscale image.\n");
    }

    free(gray);
    free_image(&img);

    return 0;
}
