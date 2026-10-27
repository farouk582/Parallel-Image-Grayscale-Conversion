
#include <stdio.h>
#include "image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int save_grayscale(const char *filename,
                   const unsigned char *gray,
                   int width,
                   int height)
{
    return stbi_write_png(
        filename, width, height, 1, gray, width
    );
}
