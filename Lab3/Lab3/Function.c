#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "BMP.h"

void negative_24bit(BMPImage* image) {
    int row_size = row_bytes(image);
    int height = abs(image->info_header.height);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < image->info_header.width; x++) {
            Pixel* pixel = (Pixel*)((unsigned char*)image->pixels + y * row_size + x * sizeof(Pixel));
            pixel->red = 255 - pixel->red;
            pixel->green = 255 - pixel->green;
            pixel->blue = 255 - pixel->blue;
        }
    }
}

void grayscale(BMPImage* image) {
    int row_size = row_bytes(image);
    int height = abs(image->info_header.height);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < image->info_header.width; x++) {
            Pixel* pixel = (Pixel*)((unsigned char*)image->pixels + y * row_size + x * sizeof(Pixel));
            unsigned char gray = (unsigned char)(0.2126 * pixel->red + 0.7152 * pixel->green + 0.0722 * pixel->blue);
            pixel->red = gray;
            pixel->green = gray;
            pixel->blue = gray;
        }
    }
}

void sort(unsigned char* red_values, unsigned char* green_values, unsigned char* blue_values) {
    for (int i = 0; i < 9; i++) {
        for (int j = i + 1; j < 9; j++) {
            if (red_values[i] > red_values[j]) {
                unsigned char temp = red_values[i];
                red_values[i] = red_values[j];
                red_values[j] = temp;
            }
            if (green_values[i] > green_values[j]) {
                unsigned char temp = green_values[i];
                green_values[i] = green_values[j];
                green_values[j] = temp;
            }
            if (blue_values[i] > blue_values[j]) {
                unsigned char temp = blue_values[i];
                blue_values[i] = blue_values[j];
                blue_values[j] = temp;
            }
        }
    }
}

void search(BMPImage* image, int row_size, int x, int y, unsigned char* red_values, unsigned char* green_values, unsigned char* blue_values) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            Pixel* pixel = (Pixel*)((unsigned char*)image->pixels + (y + i) * row_size + (x + j) * sizeof(Pixel));
            red_values[(i + 1) * 3 + (j + 1)] = pixel->red;
            green_values[(i + 1) * 3 + (j + 1)] = pixel->green;
            blue_values[(i + 1) * 3 + (j + 1)] = pixel->blue;
        }
    }
}

void median_filter(BMPImage* image) {
    int row_size = row_bytes(image);
    int height = abs(image->info_header.height);

    Pixel* new_pixels = malloc(row_size * height);
    if (!new_pixels) {
        fprintf(stderr, "Could not allocate memory for new pixel data\n");
        return;
    }

    memcpy(new_pixels, image->pixels, row_size * height);

    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < image->info_header.width - 1; x++) {
            unsigned char red_values[9];
            unsigned char green_values[9];
            unsigned char blue_values[9];

            search(image, row_size, x, y, red_values, green_values, blue_values);

            sort(red_values, green_values, blue_values);

            Pixel* new_pixel = (Pixel*)((unsigned char*)new_pixels + y * row_size + x * sizeof(Pixel));
            new_pixel->red = red_values[4];
            new_pixel->green = green_values[4];
            new_pixel->blue = blue_values[4];
        }
    }

    free(image->pixels);
    image->pixels = new_pixels;
}

void gamma_correction(BMPImage* image, double gamma) {
    int row_size = row_bytes(image);
    int height = abs(image->info_header.height);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < image->info_header.width; x++) {
            Pixel* pixel = (Pixel*)((unsigned char*)image->pixels + y * row_size + x * sizeof(Pixel));
            pixel->red = (unsigned char)(pow(pixel->red / 255.0, gamma) * 255);
            pixel->green = (unsigned char)(pow(pixel->green / 255.0, gamma) * 255);
            pixel->blue = (unsigned char)(pow(pixel->blue / 255.0, gamma) * 255);
        }
    }
}

int row_bytes(BMPImage* image) {
    int row_size = image->info_header.width * image->info_header.bit_count / 8;
    int padding = (4 - row_size % 4) % 4;
    int row_bytes = row_size + padding;
    return row_bytes;
}