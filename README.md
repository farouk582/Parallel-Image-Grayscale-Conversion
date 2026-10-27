# Parallel Image Grayscale Conversion

## 1. Project Overview

This project converts a color image into a grayscale image using C. The project is designed to use MPI for parallel processing, allowing multiple processes to work on different portions of the image.

## 2. Grayscale Conversion

A color image contains three color channels for each pixel:

- **R:** Red
- **G:** Green
- **B:** Blue

Each RGB pixel is converted into one grayscale value using the following formula:

`Gray = 0.299 * R + 0.587 * G + 0.114 * B`

The result is rounded to the nearest integer and stored as an unsigned 8-bit value.

### Implementation

The conversion function is implemented in `grayscale.c`:

```c
void rgb_to_gray(const unsigned char *rgb,
                 unsigned char *gray,
                 int pixel_count);
```

**Parameters:**
- `rgb`: Input array containing 3 bytes per pixel in RGB order.
- `gray`: Output array containing one grayscale byte per pixel.
- `pixel_count`: Number of pixels to convert.

The function converts each pixel independently and does not perform MPI communication. This allows the parallel-processing component to reuse the same function on each process's assigned pixels.

## 3. Testing the Grayscale Function

The file `test_grayscale.c` tests the conversion function using five known colors.

| Input color | RGB values | Expected grayscale |
|---|---|---:|
| Red | (255, 0, 0) | 76 |
| Green | (0, 255, 0) | 150 |
| Blue | (0, 0, 255) | 29 |
| White | (255, 255, 255) | 255 |
| Black | (0, 0, 0) | 0 |

**Test status:** All five test values matched the expected results.

### Compile and Run the Unit Test

Using GCC in Windows PowerShell:

```powershell
gcc -Wall -Wextra test_grayscale.c grayscale.c -o test_grayscale.exe
.\test_grayscale.exe
```

Expected output:

```text
Red   = 76 (expected 76)
Green = 150 (expected 150)
Blue  = 29 (expected 29)
White = 255 (expected 255)
Black = 0 (expected 0)
```

## 4. Image Loading and Output

The project uses the `stb_image` and `stb_image_write` libraries to load an input image and save the grayscale result.

- `image_io.c`: Loads the input image as RGB data and releases image memory.
- `image_output.c`: Saves the grayscale pixel array as a PNG image.
- `test_image_gray.c`: Standalone integration test for loading an image, converting it to grayscale, and saving the result.

The image integration test should be considered verified only after it compiles, runs successfully, and produces an output file that can be opened.

Example standalone test command:

```powershell
gcc -Wall -Wextra test_image_gray.c image_io.c grayscale.c image_output.c -o test_image_gray.exe
.\test_image_gray.exe
```

This standalone command does not build or test the MPI implementation.

## 5. MPI Parallel Processing — Pending Integration

The parallel-processing component is to be integrated with the grayscale conversion function.

The MPI implementation should:

1. Load the image on the root process.
2. Share image dimensions and status with other processes.
3. Divide the RGB pixel data among processes, including uneven partitions when necessary.
4. Call `rgb_to_gray()` on each process's assigned pixels.
5. Gather the grayscale results on the root process.
6. Save the final grayscale image.

`MPI_Scatterv` and `MPI_Gatherv` can be used to support uneven data partitions.

The MPI implementation and complete multi-process execution must be tested separately using a suitable MPI compiler and runtime.

**Important:** `test_grayscale.c` is a unit test for the conversion function; passing it does not verify MPI communication or parallel performance.

## 6. Current Status

- [x] Implement RGB-to-grayscale conversion.
- [x] Unit-test the conversion using five known colors.
- [ ] Verify standalone image loading, conversion, and PNG output.
- [ ] Integrate the conversion function with the MPI implementation.
- [ ] Test the complete program with multiple MPI processes.
- [ ] Compare parallel output against a sequential reference.
- [ ] Measure execution time and evaluate parallel performance.

## 7. Integration Notes

- Keep the function signature of `rgb_to_gray()` consistent across `grayscale.c`, `image.h`, and the parallel-processing implementation.
- Keep `STB_IMAGE_IMPLEMENTATION` defined in exactly one source file, such as `image_io.c`.
- Keep `STB_IMAGE_WRITE_IMPLEMENTATION` defined in exactly one source file, such as `image_output.c`.
- Coordinate shared-header changes with the team before merging.
- The standalone unit test can use GCC without MPI, provided its source files do not include MPI headers.
- The complete parallel application must use the team's configured MPI toolchain.

## 8. Project Dependencies

- A C compiler such as GCC.
- `stb_image.h` for image loading.
- `stb_image_write.h` for PNG output.
- An MPI implementation and compatible compiler wrapper for the parallel application.

Repository for the stb libraries: https://github.com/nothings/stb
