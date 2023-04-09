#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "BMP.h"
#include "Program.h"

void menu() {
    char filename[100];
    printf("Enter the filename: ");
    scanf("%s", filename);

    errno_t err;
    FILE* fp;
    err = fopen_s(&fp, filename, "rb");
    file_open(err);

    BMPImage* image = read_bmp_24(fp);

    fclose(fp);

    int choice;
    printf("Enter the operation you want to perform:\n");
    printf("1. Negative\n");
    printf("2. Grayscale\n");
    printf("3. Median filter\n");
    printf("4. Gamma correction\n");
    while (!scanf_s("%d", &choice) || choice < 1 || choice > 4 || getchar() != '\n') {
        printf("Invalid choice! Valid choice [1-4]\n");
        rewind(stdin);
        printf("Your choice: ");
    }
    switch (choice) {
    case 1:
        negative_24bit(image);
        break;
    case 2:
        grayscale(image);
        break;
    case 3:
        median_filter(image);
        break;
    case 4: {
        double gamma;
        printf("Enter the gamma value: ");
        while (!scanf_s("%lf", &gamma) || getchar() != '\n') {
            printf("Invalid gamma!\n");
            rewind(stdin);
            printf("Enter the gamma value: ");
        }
        gamma_correction(image, gamma);
        break;
    }
    default:
        fprintf(stderr, "Invalid choice\n");
        free_bmp(image);
        break;
    }

    errno_t err_out;
    FILE* fp_out;
    err_out = fopen_s(&fp_out, "output.BMP", "wb");
    file_open(err);

    write_bmp(image, fp_out);
    fclose(fp_out);

    free_bmp(image);

}

void free_bmp(BMPImage* image) {
    free(image->pixels);
    free(image);
}

void file_open(errno_t err) {

    if (err != 0) {
        printf("ERROR FILE");
        exit(1);
    }
}