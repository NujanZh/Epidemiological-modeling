#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    double S;
    double I;
    double R;
} EpidemicState;

void sir_model_s(EpidemicState *state, double b, double y) {
    double new_S = state->S - b * state->S * state->I;

    state->S = new_S;
}

void sir_model_i(EpidemicState *state, double b, double y) {
    double new_I = state->I + b * state->S * state->I - y * state->I;

    state->I = new_I;
}

void sir_model_r(EpidemicState *state, double b, double y) {
    double new_R = state->R + y * state->I;

    state->R = new_R;
}

int main() {
    int width = 30; // 0000 0111 1000 0000
    int height = 800;

    double b = 0.3;
    double y = 1.0 / 8.0;

    FILE* output_file = fopen("main.html", "wb");

    EpidemicState initial_state;
    initial_state.S = (double)1000 / 1250;
    initial_state.I = (double)200 / 1250;
    initial_state.R = (double)50 /1250;

    fprintf(output_file, "<!DOCTYPE html>\n");
    fprintf(output_file, "<html lang=\"en\">\n");
    fprintf(output_file, "<head>\n");
    fprintf(output_file, "\t<meta charset=\"UTF-8\">\n");
    fprintf(output_file, "\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n");
    fprintf(output_file, "\t<title>SIR model</title>\n");

    fprintf(output_file, "</head>\n");
    fprintf(output_file, "<body>\n");

    fprintf(output_file, "\t<svg width=\"600\" height=\"300\" viewBox=\"0 0 600 300\" xmlns=\"http://www.w3.org/2000/svg\">\n");

    fprintf(output_file, "\t\t<polyline\n");
    fprintf(output_file, "\t\t\tfill=\"none\"\n");
    fprintf(output_file, "\t\t\tstroke=\"#0074d9\"\n");
    fprintf(output_file, "\t\t\tstroke-width=\"3\"\n");
    fprintf(output_file, "\t\t\tpoints=\"\n");

    int num_s = 0;

    for (int i = 0; i < 31; i++)
    {
        num_s = num_s + 20;
        double i_num = initial_state.S * 10;
        fprintf(output_file, "\t\t\t%d, %f\n", num_s, i_num);

        sir_model_s(&initial_state, b, y);
    }

    fprintf(output_file, "\t\t\t\"\n");

    fprintf(output_file, "\t\t/>\n");

    fprintf(output_file, "\t\t<polyline\n");
    fprintf(output_file, "\t\t\tfill=\"none\"\n");
    fprintf(output_file, "\t\t\tstroke=\"#FF0000\"\n");
    fprintf(output_file, "\t\t\tstroke-width=\"3\"\n");
    fprintf(output_file, "\t\t\tpoints=\"\n");

    int num_i = 0;

    for (int i = 0; i < 31; i++)
    {
        num_i = num_i + 20;
        double i_num = initial_state.I * 10;

        fprintf(output_file, "\t\t\t%d, %f\n", num_i, i_num);

        sir_model_i(&initial_state, b, y);
    }

    fprintf(output_file, "\t\t\t\"\n");

    fprintf(output_file, "\t\t/>\n");

    fprintf(output_file, "\t</svg>\n");

    fprintf(output_file, "</body>\n");
    fprintf(output_file, "</html>\n");

    return 0;
}
