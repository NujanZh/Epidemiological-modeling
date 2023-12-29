#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    double S;
    double I;
    double R;
} EpidemicState;

void s_model(EpidemicState *state, double b, double y);
void i_model(EpidemicState *state, double b, double y);
void r_model(EpidemicState *state, double b, double y);

int check_missing_parameter(char* parameter, int count_parameter);
int check_too_many_parameters(char** argv, int i, int count_parameter);

int main(int argc, char** argv) 
{

    FILE* real_data_file = NULL;
    FILE* output_file = NULL;

    int count_real_data_arg = 0;
    int count_output_arg = 0;

    int infectious_days = 0;
    int infectious_per_day = 0;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--real-data") == 0)
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

            if (check_too_many_parameters(argv, i, infectious_days)) return 1;
            if (i >= argc || argv[i][0] == '-')
            {
                printf("Missing integer to file for %s\n", argv[i - 1]);
                return 1;
            }

            int num = atoi(argv[i]);

            infectious_days = num;

        } else if (strcmp(argv[i], "--infectious_per_day") == 0)
        {
            i++;

            if (check_too_many_parameters(argv, i, infectious_per_day)) return 1;
            if (i >= argc || argv[i][0] == '-')
            {
                printf("Missing integer to file for %s\n", argv[i - 1]);
                return 1;
            }

            int num = atoi(argv[i]);

            infectious_per_day = num;

        } else if (strcmp(argv[i], "--output") == 0)
        {
            i++;
            count_output_arg++;

            if (check_too_many_parameters(argv, i, count_output_arg)) return 1;
            if (i >= argc || argv[i][0] == '-')
            {
                printf("Missing path to file for %s\n", argv[i - 1]);
                return 1;
            }

            output_file = fopen(argv[i], "wb");
        }
    }

    check_missing_parameter("--real-data", count_real_data_arg);
    check_missing_parameter("--infectious_days", infectious_days);
    check_missing_parameter("--infectious_per_day", infectious_per_day);
    check_missing_parameter("--output", count_output_arg);

    double b = infectious_per_day;
    double y = 1.0 / (double)infectious_days;

    EpidemicState state;

    fclose(real_data_file);
    fclose(output_file);

    return 0;
}

void s_model(EpidemicState *state, double b, double y)
{
    double new_s = state->S - b * state->S * state->I;
    state->S = new_s;
}

void i_model(EpidemicState *state, double b, double y)
{
    double new_i = state->I + b * state->S * state->I - y * state->I;
    state->I = new_i;
}
void r_model(EpidemicState *state, double b, double y)
{
    double new_r = state->R + y * state->I;
    state->R = new_r;
}

int check_missing_parameter(char* parameter, int count_parameter)
{
    if (count_parameter < 1) {
        printf("Parameter %s didn't provided\n", parameter);
        return 1;
    }
}

int check_too_many_parameters(char** argv, int i, int count_parameter)
{
    if (count_parameter > 1) {
        printf("Parameter %s provided multiple times\n", argv[i - 1]);
        return 1;
    }

    return 0;
}
