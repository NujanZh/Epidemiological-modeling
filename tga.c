#include <stdio.h>
#include <string.h>
#include "tga.h"

void save_tga(char* filename, TGAHeader header, RGBPixel* image) {

    int width = 0;
    int height = 0;

    memcpy(&width, header.width, sizeof(header.width));
    memcpy(&height, header.height, sizeof(header.height));

    printf("%d\n", width);
    printf("%d\n", height);

    FILE* output = fopen(filename, "wb");

    fwrite(&header, sizeof(header), 1, output);
    fwrite(image, sizeof(RGBPixel), width * height, output);

    fclose(output);
}
