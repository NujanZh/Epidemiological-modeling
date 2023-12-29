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
    char buffer[1000];
    char *data;
    int days = 0;

    FILE* real_data_file = NULL;
    FILE* output_file = NULL;

    int count_real_data_arg = 0;
    int count_output_arg = 0;
    int count_infectious_days = 0;
    int count_infections_per_day = 0;

    int infectious_days = 0;
    double infections_per_day = 0;

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
            count_infectious_days++;

            if (check_too_many_parameters(argv, i, count_infectious_days)) return 1;
            if (i >= argc || argv[i][0] == '-')
            {
                printf("Missing integer to file for %s\n", argv[i - 1]);
                return 1;
            }

            int num = atoi(argv[i]);

            infectious_days = num;

        } else if (strcmp(argv[i], "--infections_per_day") == 0)
        {
            i++;
            count_infections_per_day++;

            if (check_too_many_parameters(argv, i, count_infections_per_day)) return 1;
            if (i >= argc || argv[i][0] == '-')
            {
                printf("Missing integer to file for %s\n", argv[i - 1]);
                return 1;
            }

            double num = atof(argv[i]);

            infections_per_day = num;

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
    check_missing_parameter("--infectious_days", count_infectious_days);
    check_missing_parameter("--infections_per_day", count_infections_per_day);
    check_missing_parameter("--output", count_output_arg);

    double b = infections_per_day;
    double y = 1.0 / (double)infectious_days;


    fgets(buffer, sizeof(buffer), real_data_file);

    data = strtok(buffer, ",");
    int susceptible_number_start = atoi(data);

    data = strtok(NULL, ",");
    int infected_number_start = atoi(data);

    data = strtok(NULL, ",");
    int recovered_number_start = atoi(data);

    int total_number = susceptible_number_start + infected_number_start + recovered_number_start;

    while(fgets(buffer, sizeof(buffer), real_data_file))
    {
        if (days == 0)
        {
            printf("%d %d %d\n", susceptible_number_start, infected_number_start, recovered_number_start);
            days++;
        }

        data = strtok(buffer, ",");
        int susceptible_number = atoi(data);

        data = strtok(NULL, ",");
        int infected_number = atoi(data);

        data = strtok(NULL, ",");
        int recovered_number = atoi(data);

        printf("%d %d %d\n", susceptible_number, infected_number, recovered_number);

        days++;
    }

    printf("%d\n", days);

    EpidemicState state;
    state.S = (double) susceptible_number_start / total_number;
    state.I = (double) infected_number_start / total_number;
    state.R = (double) recovered_number_start / total_number;

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
