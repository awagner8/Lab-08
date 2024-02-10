#include "image_util.h"
#include <stdio.h>
#include <stdlib.h>

// Function to invert the pixel values
void invertPixels(unsigned char* pixels, size_t numPixels) {
    for (size_t i = 0; i < numPixels; ++i) {
        pixels[i] = 255 - pixels[i]; // Invert each pixel value
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s input.ppm output.ppm\n", argv[0]);
        return 1;
    }

    // Open input file
    FILE* inputFile = fopen(argv[1], "rb");
    if (!inputFile) {
        perror("Error opening input file");
        return 1;
    }

    // Read PPM header
    char magic[3];
    int width, height, colors;
    fscanf(inputFile, "%2s %d %d %d\n", magic, &width, &height, &colors);

    // Check if the format is P6 (binary PPM)
    if (magic[0] != 'P' || magic[1] != '6') {
        printf("Invalid PPM format. Only binary PPM (P6) is supported.\n");
        fclose(inputFile);
        return 1;
    }

    // Allocate memory for pixel data
    size_t numPixels = width * height*3;
    unsigned char* pixels = (unsigned char*)malloc(3 * numPixels);
    if (!pixels) {
        perror("Memory allocation failed");
        fclose(inputFile);
        return 1;
    }

    // Read pixel data
    fread(pixels, 1, 3 * numPixels, inputFile);
    fclose(inputFile);

    // Invert pixel values
    invertPixels(pixels, numPixels);

    // Open output file
    FILE* outputFile = fopen(argv[2], "wb");
    if (!outputFile) {
        perror("Error opening output file");
        free(pixels);
        return 1;
    }

    // Write PPM header
    fprintf(outputFile, "P6\n%d %d\n%d\n", width, height, colors);

    // Write inverted pixel data
    fwrite(pixels, 1,  numPixels, outputFile);
    fclose(outputFile);

    free(pixels);
    printf("Image transformation complete. Output written to %s\n", argv[2]);
    return 0;
}