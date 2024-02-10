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


/*typedef struct {
     unsigned char red,green,blue;
} PPMPixel;

typedef struct {
     int x, y;
     int colors;
     PPMPixel **data;
} PPMImage;

#define CREATOR "RPFELGUEIRAS"
#define RGB_COMPONENT_COLOR 255

static PPMImage *readPPM(const char *filename)
{
         char buff[16];
         PPMImage *img;
         FILE *fp;
         int c, rgb_comp_color;
         //open PPM file for reading
         fp = fopen(filename, "rb");
         if (!fp) {
              fprintf(stderr, "Unable to open file '%s'\n", filename);
              exit(1);
         }

         //read image format
         if (!fgets(buff, sizeof(buff), fp)) {
              perror(filename);
              exit(1);
         }

    //check the image format
    if (buff[0] != 'P' || buff[1] != '6') {
         fprintf(stderr, "Invalid image format (must be 'P6')\n");
         exit(1);
    }

    //alloc memory form image
    img = (PPMImage *)malloc(sizeof(PPMImage));
    if (!img) {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }

    //check for comments
    c = getc(fp);
    while (c == '#') {
    while (getc(fp) != '\n') ;
         c = getc(fp);
    }

    ungetc(c, fp);
    //read image size information
    if (fscanf(fp, "%d %d", &img->x, &img->y) != 2) {
         fprintf(stderr, "Invalid image size (error loading '%s')\n", filename);
         exit(1);
    }

    //read rgb component
    if (fscanf(fp, "%d", &rgb_comp_color) != 1) {
         fprintf(stderr, "Invalid rgb component (error loading '%s')\n", filename);
         exit(1);
    }

    //check rgb component depth
    if (rgb_comp_color!= RGB_COMPONENT_COLOR) {
         fprintf(stderr, "'%s' does not have 8-bits components\n", filename);
         exit(1);
    }

    while (fgetc(fp) != '\n') ;
    //memory allocation for pixel data
    img->data = (PPMPixel*)malloc(img->x * img->y * sizeof(PPMPixel));

    if (!img) {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }

    //read pixel data from file
    if (fread(img->data, 3 * img->x, img->y, fp) != img->y) {
         fprintf(stderr, "Error loading image '%s'\n", filename);
         exit(1);
    }

    fclose(fp);
    return img;
}


PPMImage *invertImage(PPMImage *myPic) {
    int i, j;
    for (i = 0; i < myPic->x; ++i) {
        for (j = 0; j < myPic->y; ++j) {
            // Inversion requires subtracting the actual value from the max color value
            myPic->data[i][j].red = myPic->colors - myPic->data[i][j].red;
            myPic->data[i][j].green = myPic->colors - myPic->data[i][j].green;
            myPic->data[i][j].blue = myPic->colors - myPic->data[i][j].blue;
        }
    }
    return myPic;
}

int main(){
    FILE *file = (sample.ppm, "");
    //changeColorPPM(image);
    //writePPM("can_bottom2.ppm",image);
    //printf("Press any key...");
    //getchar();
    my_fwrite(image, sizeof(image), size_t num_data, FILE* dest);
    return 0;
}*/
