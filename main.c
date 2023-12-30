#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    double S;
    double I;
    double R;
} EpidemicState;

void make_sir_model(EpidemicState *state, double b, double y);

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
                printf("Missing integer number for %s\n", argv[i - 1]);
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
                printf("Missing float number for %s\n", argv[i - 1]);
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

    fprintf(output_file, "<!DOCTYPE html>\n");
    fprintf(output_file, "<html lang=\"en\">\n");
    fprintf(output_file, "<head>\n");
    fprintf(output_file, "\t<meta charset=\"UTF-8\">\n");
    fprintf(output_file, "\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n");
    fprintf(output_file, "\t<title>SIR model</title>\n");
    fprintf(output_file, "</head>\n");

    fprintf(output_file, "<body>\n");

    fprintf(output_file, "<div>\n");
    fprintf(output_file, "<div style=\"display: inline-block\">\n");
    fprintf(output_file, "<h2>Real data </h2>\n");
    fprintf(output_file, "\t<svg style=\"transform: scaleY(-1)\" width=\"600\" height=\"500\" viewBox=\"0 0 600 500\" xmlns=\"http://www.w3.org/2000/svg\">\n");

    fprintf(output_file, "\t\t<polyline\n");
    fprintf(output_file, "\t\t\tfill=\"none\"\n");
    fprintf(output_file, "\t\t\tstroke=\"#0000FF\"\n");
    fprintf(output_file, "\t\t\tstroke-width=\"2\"\n");
    fprintf(output_file, "\t\t\tpoints=\"\n");

    int num = 0;

    while(fgets(buffer, sizeof(buffer), real_data_file))
    {
        double i;

        if (days == 0)
        {
            i = (double) susceptible_number_start / total_number;
            i = i * 500;
            fprintf(output_file, "\t\t\t%d, %f\n", num, i);

            num = num + 20;
            days++;
        }

        data = strtok(buffer, ",");
        int susceptible_number = atoi(data);
        i = (double) susceptible_number / total_number;
        i = i * 500;

        data = strtok(NULL, ",");
        int infected_number = atoi(data);

        data = strtok(NULL, ",");
        int recovered_number = atoi(data);

        fprintf(output_file, "\t\t\t%d, %f\n", num, i);

        num = num + 20;
        days++;
    }

    fprintf(output_file, "\t\t\t\"\n");

    fprintf(output_file, "\t\t/>\n");

    fprintf(output_file, "\t\t<polyline\n");
    fprintf(output_file, "\t\t\tfill=\"none\"\n");
    fprintf(output_file, "\t\t\tstroke=\"#FF0000\"\n");
    fprintf(output_file, "\t\t\tstroke-width=\"2\"\n");
    fprintf(output_file, "\t\t\tpoints=\"\n");

    // Need this to read a real_data_file from the beginning
    rewind(real_data_file);

    num = 0;
    while(fgets(buffer, sizeof(buffer), real_data_file))
    {
        double i;

        data = strtok(buffer, ",");
        int susceptible_number = atoi(data);

        data = strtok(NULL, ",");
        int infected_number = atoi(data);
        i = (double) infected_number / total_number;
        i = i * 500;

        data = strtok(NULL, ",");
        int recovered_number = atoi(data);

        fprintf(output_file, "\t\t\t%d, %f\n", num, i);

        num = num + 20;
    }

    fprintf(output_file, "\t\t\t\"\n");
    fprintf(output_file, "\t\t/>\n");

    fprintf(output_file, "\t\t<polyline\n");
    fprintf(output_file, "\t\t\tfill=\"none\"\n");
    fprintf(output_file, "\t\t\tstroke=\"#00FF00\"\n");
    fprintf(output_file, "\t\t\tstroke-width=\"2\"\n");
    fprintf(output_file, "\t\t\tpoints=\"\n");

    // Need this to read a real_data_file from the beginning
    rewind(real_data_file);

    num = 0;
    while(fgets(buffer, sizeof(buffer), real_data_file))
    {
        double i;

        data = strtok(buffer, ",");
        int susceptible_number = atoi(data);

        data = strtok(NULL, ",");
        int infected_number = atoi(data);

        data = strtok(NULL, ",");
        int recovered_number = atoi(data);
        i = (double) recovered_number / total_number;
        i = i * 500;

        fprintf(output_file, "\t\t\t%d, %f\n", num, i);

        num = num + 20;
    }

    fprintf(output_file, "\t\t\t\"\n");
    fprintf(output_file, "\t\t/>\n");


    fprintf(output_file, "\t</svg>\n");
    fprintf(output_file, "</div>\n");

    EpidemicState analyze_state;
    analyze_state.S = (double) susceptible_number_start / total_number;
    analyze_state.I = (double) infected_number_start / total_number;
    analyze_state.R = (double) recovered_number_start / total_number;

    fprintf(output_file, "<div style=\"display: inline-block\">\n");
    fprintf(output_file, "<h2>Simulated data </h2>\n");
    fprintf(output_file, "\t<svg style=\"transform: scaleY(-1)\" width=\"600\" height=\"500\" viewBox=\"0 0 600 500\" xmlns=\"http://www.w3.org/2000/svg\">\n");

    fprintf(output_file, "\t\t<polyline\n");
    fprintf(output_file, "\t\t\tfill=\"none\"\n");
    fprintf(output_file, "\t\t\tstroke=\"#0000FF\"\n");
    fprintf(output_file, "\t\t\tstroke-width=\"2\"\n");
    fprintf(output_file, "\t\t\tpoints=\"\n");

    num = 0;
    for (int i = 0; i < days; ++i) {
        double result = analyze_state.S  * 500;
        fprintf(output_file, "\t\t\t%d, %f\n", num, result);
        make_sir_model(&analyze_state, b, y);
        num = num + 20;
    }

    fprintf(output_file, "\t\t\t\"\n");
    fprintf(output_file, "\t\t/>\n");

    analyze_state.S = (double) susceptible_number_start / total_number;
    analyze_state.I = (double) infected_number_start / total_number;
    analyze_state.R = (double) recovered_number_start / total_number;

    fprintf(output_file, "\t\t<polyline\n");
    fprintf(output_file, "\t\t\tfill=\"none\"\n");
    fprintf(output_file, "\t\t\tstroke=\"#FF0000\"\n");
    fprintf(output_file, "\t\t\tstroke-width=\"2\"\n");
    fprintf(output_file, "\t\t\tpoints=\"\n");

    num = 0;
    for (int i = 0; i < days; ++i) {
        double result = analyze_state.I  * 500;
        fprintf(output_file, "\t\t\t%d, %f\n", num, result);
        make_sir_model(&analyze_state, b, y);
        num = num + 20;
    }

    fprintf(output_file, "\t\t\t\"\n");
    fprintf(output_file, "\t\t/>\n");

    analyze_state.S = (double) susceptible_number_start / total_number;
    analyze_state.I = (double) infected_number_start / total_number;
    analyze_state.R = (double) recovered_number_start / total_number;

    fprintf(output_file, "\t\t<polyline\n");
    fprintf(output_file, "\t\t\tfill=\"none\"\n");
    fprintf(output_file, "\t\t\tstroke=\"#00FF00\"\n");
    fprintf(output_file, "\t\t\tstroke-width=\"2\"\n");
    fprintf(output_file, "\t\t\tpoints=\"\n");

    num = 0;
    for (int i = 0; i < days; ++i) {
        double result = analyze_state.R  * 500;
        fprintf(output_file, "\t\t\t%d, %f\n", num, result);
        make_sir_model(&analyze_state, b, y);
        num = num + 20;
    }

    fprintf(output_file, "\t\t\t\"\n");
    fprintf(output_file, "\t\t/>\n");
    fprintf(output_file, "\t</svg>\n");
    fprintf(output_file, "</div>\n");
    fprintf(output_file, "</div>\n");

    fprintf(output_file, "</body>\n");
    fprintf(output_file, "</html>\n");



    fclose(real_data_file);
    fclose(output_file);

    return 0;
}

void make_sir_model(EpidemicState *state, double b, double y)
{
    double new_s = state->S - b * state->S * state->I;
    double new_i = state->I + b * state->S * state->I - y * state->I;
    double new_r = state->R + y * state->I;

    state->S = new_s;
    state->I = new_i;
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
