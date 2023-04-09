#ifndef LAB3_BMP
#define LAB3_BMP

#pragma pack(push, 1)
typedef struct {
    unsigned short type;
    unsigned int size;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int offset;
} BMPHeader;

typedef struct {
    unsigned int size;
    int width;
    int height;
    unsigned short planes;
    unsigned short bit_count;
    unsigned int compression;
    unsigned int size_image;
    int x_pels_per_meter;
    int y_pels_per_meter;
    unsigned int clr_used;
    unsigned int clr_important;
} BMPInfoHeader;

typedef struct {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
} Pixel;

typedef struct {
    BMPHeader header;
    BMPInfoHeader info_header;
    Pixel* pixels;
} BMPImage;
#pragma pack (pop)

#endif
