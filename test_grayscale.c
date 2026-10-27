#include <stdio.h>

void rgb_to_gray(const unsigned char *rgb,
                 unsigned char *gray,
                 int pixel_count);

int main(void)
{
    unsigned char rgb[] = {
        255, 0, 0,       /* Red */
        0, 255, 0,       /* Green */
        0, 0, 255,       /* Blue */
        255, 255, 255,   /* White */
        0, 0, 0          /* Black */
    };

    unsigned char gray[5];

    rgb_to_gray(rgb, gray, 5);

    printf("Red   = %d (expected 76)\n", gray[0]);
    printf("Green = %d (expected 150)\n", gray[1]);
    printf("Blue  = %d (expected 29)\n", gray[2]);
    printf("White = %d (expected 255)\n", gray[3]);
    printf("Black = %d (expected 0)\n", gray[4]);

    return 0;
}