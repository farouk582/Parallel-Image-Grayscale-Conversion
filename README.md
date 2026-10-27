# Parallel Image Grayscale Conversion

## 1. Project Overview

This project converts a color image into a grayscale image using C and MPI (Message Passing Interface).

MPI distributes image pixels across multiple processes. Each process converts its assigned pixels to grayscale, and the root process gathers the results and saves the output image.

## 2. Grayscale Conversion

Each RGB pixel contains three color channels:

- R: Red
- G: Green
- B: Blue

The grayscale value is calculated using:

`Gray = 0.299 * R + 0.587 * G + 0.114 * B`

The result is rounded to the nearest integer and stored as an unsigned 8-bit value.

## 3. Project Structure

| File | Description |
|---|---|
| `main.c` | Initializes MPI and receives the input and output image paths from command-line arguments. |
| `image.h` | Defines the `Image` structure and the function prototypes used by the project. |
| `parallel.c` | Coordinates parallel processing, distributes RGB data, and gathers grayscale results. |
| `grayscale.c` | Implements the RGB-to-grayscale conversion function. |
| `image_io.c` | Loads images into memory using `stb_image`. |
| `image_output.c` | Saves grayscale images as PNG files using `stb_image_write`. |
| `stb_image.h` | Library used to load image files. |
| `stb_image_write.h` | Library used to write image files. |
| `test_grayscale.c` | Tests the grayscale conversion function with known RGB values. |
| `test_image_gray.c` | Tests image loading, grayscale conversion, and image saving. |

## 4. How MPI Processing Works

1. The root process loads the input image.
2. Image dimensions and processing status are shared with all processes.
3. The RGB pixel data is divided among the processes using `MPI_Scatterv`.
4. Each process converts its assigned pixels using `rgb_to_gray()`.
5. The grayscale results are collected by the root process using `MPI_Gatherv`.
6. The root process saves the final grayscale image to the requested output path.

## 5. Requirements

- GCC or a compatible C compiler.
- An MPI implementation, such as Open MPI.
- The provided `stb_image.h` and `stb_image_write.h` files.
- An input image supported by `stb_image`.

## 6. Build the Project

Compile the MPI application from the project directory:

```bash
mpicc -Wall -Wextra main.c image_io.c grayscale.c parallel.c image_output.c -o parallel.exe -lm
```

## 7. Run the Project

The program accepts two command-line arguments:

1. Input image path.
2. Output image path.

Example using four MPI processes:

```bash
mpirun -np 4 ./parallel.exe input1.jpg output1.png
```

Process another image and use a different output filename:

```bash
mpirun -np 4 ./parallel.exe input2.jpg output2.png
```

The output image is saved to the path provided as the second argument. Make sure the destination directory exists before running the program.

## 8. Testing the Grayscale Function

Compile the grayscale unit test separately:

```bash
gcc -Wall -Wextra test_grayscale.c grayscale.c -o test_grayscale.exe
```

Run it:

```bash
./test_grayscale.exe
```

The unit test checks known RGB colors and their expected grayscale values.

This test checks the conversion function only; it does not verify MPI communication.

## 9. Dependencies

The project uses the `stb` single-header libraries for image loading and writing.

Repository: https://github.com/nothings/stb

## 10. Notes

- The grayscale conversion formula remains unchanged.
- MPI uses `MPI_Scatterv` and `MPI_Gatherv` to distribute and collect pixel data.
- The input and output paths are supplied when running the application.
- The output filename can be changed for each run.
