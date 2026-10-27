
#include <stdio.h>
#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int load_image(const char *filename, Image *img)
{
    if (filename == NULL || img == NULL)
    {
        fprintf(stderr, "Error: Invalid input.\n");
        return 0;
    }

    /* Initialize image fields */
    img->width = 0;
    img->height = 0;
    img->channels = 0;
    img->data = NULL;

    /* Load the image as RGB */
    img->data = stbi_load(
        filename,
        &img->width,
        &img->height,
        &img->channels,
        3
    );

    if (img->data == NULL)
    {
        fprintf(stderr, "Error: Cannot load image '%s': %s\n",
                filename, stbi_failure_reason());
        img->width = 0;
        img->height = 0;
        img->channels = 0;
        return 0;
    }

    img->channels = 3;

    printf("Image loaded successfully!\n");
    printf("Width: %d\n", img->width);
    printf("Height: %d\n", img->height);
    printf("Channels: %d (RGB)\n", img->channels);

    return 1;
}

void free_image(Image *img)
{
    if (img == NULL)
    {
        return;
    }

    if (img->data != NULL)
    {
        stbi_image_free(img->data);
        img->data = NULL;
    }

    img->width = 0;
    img->height = 0;
    img->channels = 0;
}
