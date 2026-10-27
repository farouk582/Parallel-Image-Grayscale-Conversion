#include "image.h"

void rgb_to_gray(const unsigned char *rgb,
                 unsigned char *gray,
                 int pixel_count)
{
    for (int i = 0; i < pixel_count; i++)
    {
        unsigned char r = rgb[i * 3];
        unsigned char g = rgb[i * 3 + 1];
        unsigned char b = rgb[i * 3 + 2];

        gray[i] = (unsigned char)(
            0.299 * r +
            0.587 * g +
            0.114 * b +
            0.5
        );
    }
}
