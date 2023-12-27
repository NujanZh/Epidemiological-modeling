#ifndef _TGA_H_ 
#define _TGA_H_

#include <stdint.h>

typedef struct {
    uint8_t id_length;
    uint8_t color_map_type;
    uint8_t image_type;
    uint8_t color_map[5]; // Если больше чем один байт, то его можно написать как массив байтев
    uint8_t x_origin[2];
    uint8_t y_origin[2];
    uint8_t width[2];
    uint8_t height[2];
    uint8_t depth;
    uint8_t descriptor;
} TGAHeader;

typedef struct {
    uint8_t B;
    uint8_t G;
    uint8_t R;
} RGBPixel;

void save_tga(char* filename, TGAHeader header, RGBPixel* image);

#endif
