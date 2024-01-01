#include "sirmodel.h"

void make_sir_model(EpidemicState *state, double b, double y)
{
    double new_s = state->S - b * state->S * state->I;
    double new_i = state->I + b * state->S * state->I - y * state->I;
    double new_r = state->R + y * state->I;

    state->S = new_s;
    state->I = new_i;
    state->R = new_r;
}
void real_data_model(FILE* output_file, FILE* real_data_file, int total_number, int* days, int scale, char* color, int s_true, int i_true, int r_true)
{
    char buffer[1000];
    char *data;

    fprintf(output_file, "\t\t<polyline\n");
    fprintf(output_file, "\t\t\tfill=\"none\"\n");
    fprintf(output_file, "\t\t\tstroke=\"%s\"\n", color);
    fprintf(output_file, "\t\t\tstroke-width=\"2\"\n");
    fprintf(output_file, "\t\t\tpoints=\"\n");

    int num = 0;
    int day = 0;

    while(fgets(buffer, sizeof(buffer), real_data_file))
    {
        double result;

        data = strtok(buffer, ",");
        for (int i = 0; i < 3; ++i)
        {
            if (i == 0 && s_true == 1)
            {
                int susceptible_number = atoi(data);
                result = (double) susceptible_number / total_number;
                result = result * scale;
            }
            else if (i == 1 && i_true == 1)
            {
                int infected_number = atoi(data);
                result = (double) infected_number / total_number;
                result = result * scale;
            }
            else if (i == 2 && r_true == 1)
            {
                int recovered_number = atoi(data);
                result = (double) recovered_number / total_number;
                result = result * scale;
            }
            data = strtok(NULL, ",");
        }

        fprintf(output_file, "\t\t\t%d, %f\n", num, result);

        num = num + 20;
        day++;
    }

    *days = day;

    fprintf(output_file, "\t\t\t\"\n");
    fprintf(output_file, "\t\t/>\n");
}

void analyze_data_model(EpidemicState* analyze_state, FILE* output_file, int days, int scale, char* color, double b, double y, int s_true, int i_true, int r_true)
{
    fprintf(output_file, "\t\t<polyline\n");
    fprintf(output_file, "\t\t\tfill=\"none\"\n");
    fprintf(output_file, "\t\t\tstroke=\"%s\"\n", color);
    fprintf(output_file, "\t\t\tstroke-width=\"2\"\n");
    fprintf(output_file, "\t\t\tpoints=\"\n");

    int num = 0;
    for (int i = 0; i < days; ++i) {
        if (s_true == 1)
        {
            double result = analyze_state->S  * scale;
            fprintf(output_file, "\t\t\t%d, %f\n", num, result);
            make_sir_model(analyze_state, b, y);
        }
        if (i_true == 1)
        {
            double result = analyze_state->I  * scale;
            fprintf(output_file, "\t\t\t%d, %f\n", num, result);
            make_sir_model(analyze_state, b, y);
        }
        if (r_true == 1)
        {
            double result = analyze_state->R  * scale;
            fprintf(output_file, "\t\t\t%d, %f\n", num, result);
            make_sir_model(analyze_state, b, y);
        }
        num = num + 20;
    }

    fprintf(output_file, "\t\t\t\"\n");
    fprintf(output_file, "\t\t/>\n");
}
