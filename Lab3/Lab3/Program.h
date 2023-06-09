#ifndef LAB3_PROGRAM_HEADER
#define LAB3_PROGRAM_HEADER
#include "BMP.h"

void negative_24bit(BMPImage* image);
void grayscale(BMPImage* image);
void median_filter(BMPImage* image);
void gamma_correction(BMPImage* image, double gamma);
BMPImage* read_bmp_24(FILE* fp);
void write_bmp(BMPImage* image, FILE* fp);
void free_bmp(BMPImage* image);
void file_open(errno_t err);
int row_bytes(BMPImage* image);
void menu();
void free_bmp(BMPImage* image);
void file_open(errno_t err);
void sort(unsigned char* red_values, unsigned char* green_values, unsigned char* blue_values);
void search(BMPImage* image, int row_size, int x, int y, unsigned char* red_values, unsigned char* green_values, unsigned char* blue_values);
#endif

