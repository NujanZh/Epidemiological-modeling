#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "tga.h" 

int check_missing_parameter(char* parameter, int count_parameter);
int check_too_many_parameters(char** argv, int i, int count_parameter);

int main(int argc, char** argv) {

    FILE* real_data_file = NULL;

    int width = 1920;
    int height = 1080;

    int count_real_data_arg = 0;
    int count_infectious_days_arg = 0;
    int count_infectious_per_day_arg = 0;
    int count_output_arg = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--real_data") == 0)
        {
            i++;
            count_real_data_arg++;

            if (check_too_many_parameters(argv, i, count_real_data_arg)) return 1;
            if (i >= argc || argv[i][0] == '-')
            {
                printf("Missing path to file for %s\n", argv[i - 1]);
                return 1;
            }

            real_data_file = fopen(argv[i], "rb");

        } else if (strcmp(argv[i], "--infectious_days") == 0)
        {
            i++;
            count_inflectious_days_arg++;

            if (check_too_many_parameters(argv, i, count_infectious_days_arg)) return 1;
            if (i >= argc || argv[i][0] == '-')
            {
                printf("Missing integer to file for %s\n", argv[i - 1]);
                return 1;
            }

        } else if (strcmp(argv[i], "--infectious_per_day") == 0)
        {

        } else if (strcmp(argv[i], "--output"))
        {

        }
    }

    check_missing_parameter("--read_data", count_real_data_arg);
    check_missing_parameter("--infectious_days", count_infectious_days_arg);
    check_missing_parameter("--infectious_per_day", count_infectious_per_day_arg);
    check_missing_parameter("--output", count_output_arg);

    TGAHeader header = { 0, 0, 2, { 0, 0, 0, 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, 24, 32 };

    memcpy(header.width, &width, sizeof(header.width));
    memcpy(header.height, &height, sizeof(header.height));

    RGBPixel* image = malloc(sizeof(RGBPixel) * width * height);

    for (int x = 0; x < width; x++) {
        int y = (height/2) + (height/2) * sin(2 * 3.141593 * (x/(double)width));
        image[y * width + x].R = 255;
        image[y * width + x].G = 255;
        image[y * width + x].B = 255;
    }

    save_tga("image.tga", header, image);

    free(image);

    return 0;

    return 0;
}

int check_missing_parameter(char* parameter, int count_parameter)
{
    if (count_parameter < 1) {
        printf("Parameter %s didn't provided\n", parameter);
        return 1;
    }
}

int check_to_many_parameters(char** argv, int i, int count_parameter)
{
    if (count_parameter > 1) {
        printf("Parameter %s provided multiple times\n", argv[i - 1]);
        return 1;
    }
}
