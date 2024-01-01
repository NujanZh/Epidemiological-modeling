#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sirmodel.h"
#include "checkparameter.h"

int main(int argc, char** argv) 
{
    char buffer[1000];
    char *data;

    // this parameter will count a days from real data file in function real_data_model then I will use for loop in function analyze data model
    int days = 0;

    FILE* real_data_file = NULL;
    FILE* output_file = NULL;

    // this parameters will count how many times user write a parameters, if it will be more than 1 code will throw error
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

            // check how many times this parameter was called
            if (check_too_many_parameters(argv, i, count_real_data_arg)) return 1;
            if (i >= argc || argv[i][0] == '-')
            {
                printf("Missing path to file for %s\n", argv[i - 1]);
                return 1;
            }

            real_data_file = fopen(argv[i], "rb");

            if (real_data_file == NULL)
            {
                printf("Please check if you write real data file\'s name or path correct.\nBecause the file you wrote doesn't exist.\n");
                return 1;
            }

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

    // check if all parameters have been written
    check_missing_parameter("--real-data", count_real_data_arg);
    check_missing_parameter("--infectious_days", count_infectious_days);
    check_missing_parameter("--infections_per_day", count_infections_per_day);
    check_missing_parameter("--output", count_output_arg);

    double b = infections_per_day;
    double y = 1.0 / (double)infectious_days;

    // call function fgets to save a starting numbers from real data file
    fgets(buffer, sizeof(buffer), real_data_file);

    data = strtok(buffer, ",");
    int susceptible_number_start = atoi(data);

    data = strtok(NULL, ",");
    int infected_number_start = atoi(data);

    data = strtok(NULL, ",");
    int recovered_number_start = atoi(data);

    int total_number = susceptible_number_start + infected_number_start + recovered_number_start;

    // using rewind to read a real data file from the beginning
    rewind(real_data_file);

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

    real_data_model(output_file, real_data_file, total_number, &days, 500, "#0000FF", 1, 0, 0);
    // Using rewind because real_data_model function draw polyline for each SIR argument separately
    rewind(real_data_file);

    real_data_model(output_file, real_data_file, total_number, &days, 500, "#FF0000", 0, 1, 0);
    rewind(real_data_file);

    real_data_model(output_file, real_data_file, total_number, &days, 500, "#00FF00", 0, 0, 1);
    rewind(real_data_file);

    fprintf(output_file, "\t</svg>\n");
    fprintf(output_file, "</div>\n");


    fprintf(output_file, "<div style=\"display: inline-block\">\n");
    fprintf(output_file, "<h2>Simulated data </h2>\n");
    fprintf(output_file, "\t<svg style=\"transform: scaleY(-1)\" width=\"600\" height=\"500\" viewBox=\"0 0 600 500\" xmlns=\"http://www.w3.org/2000/svg\">\n");

    EpidemicState analyze_state;

    analyze_state.S = (double) susceptible_number_start / total_number;
    analyze_state.I = (double) infected_number_start / total_number;
    analyze_state.R = (double) recovered_number_start / total_number;

    analyze_data_model(&analyze_state, output_file, days, 500, "#0000FF", b, y, 1, 0, 0);

    // I wrote the original data again because I call the analyze_data_model function for each argument separately. This is done this way because I have to draw a polyline for each argument.
    analyze_state.S = (double) susceptible_number_start / total_number;
    analyze_state.I = (double) infected_number_start / total_number;
    analyze_state.R = (double) recovered_number_start / total_number;

    analyze_data_model(&analyze_state, output_file, days, 500, "#FF0000", b, y, 0, 1, 0);

    analyze_state.S = (double) susceptible_number_start / total_number;
    analyze_state.I = (double) infected_number_start / total_number;
    analyze_state.R = (double) recovered_number_start / total_number;

    analyze_data_model(&analyze_state, output_file, days, 500, "#00FF00", b, y, 0, 0, 1);

    fprintf(output_file, "\t</svg>\n");
    fprintf(output_file, "</div>\n");
    fprintf(output_file, "</div>\n");

    fprintf(output_file, "</body>\n");
    fprintf(output_file, "</html>\n");



    fclose(real_data_file);
    fclose(output_file);

    return 0;
}