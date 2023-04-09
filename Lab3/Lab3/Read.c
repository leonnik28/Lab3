#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "BMP.h"
#include "Program.h"

BMPImage* read_bmp_24(FILE* fp) {
    BMPImage* image = malloc(sizeof(BMPImage));
    if (!image) {
        fprintf(stderr, "Could not allocate memory for image\n");
        return NULL;
    }

    fread(&image->header, sizeof(BMPHeader), 1, fp);
    fread(&image->info_header, sizeof(BMPInfoHeader), 1, fp);

    if (image->header.type != 0x4D42) {
        fprintf(stderr, "Not a BMP file\n");
        free(image);
        return NULL;
    }

    fseek(fp, image->header.offset, SEEK_SET);

    int row_size = row_bytes(image);
    int pixel_array_size = row_size * abs(image->info_header.height);
    image->pixels = malloc(pixel_array_size);
    if (!image->pixels) {
        fprintf(stderr, "Could not allocate memory for pixel data\n");
        free(image);
        return NULL;
    }

    fread(image->pixels, pixel_array_size, 1, fp);

    return image;
}

void write_bmp(BMPImage* image, FILE* fp) {
    fwrite(&image->header, sizeof(BMPHeader), 1, fp);
    fwrite(&image->info_header, sizeof(BMPInfoHeader), 1, fp);

    fseek(fp, image->header.offset, SEEK_SET);

    int row_size = row_bytes(image);
    int pixel_array_size = row_size * abs(image->info_header.height);

    fwrite(image->pixels, pixel_array_size, 1, fp);
}