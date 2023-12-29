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

    fprintf(output_file, "\t<style>\n");
    fprintf(output_file, "\t\t.chart {\n");
    fprintf(output_file, "\t\t\t background: white;\n");
    fprintf(output_file, "\t\t\t width: 500px;\n");
    fprintf(output_file, "\t\t\t height: 500px;\n");
    fprintf(output_file, "\t\t\t border-left: 1px dotted #555;\n");
    fprintf(output_file, "\t\t\t border-bottom: 1px dotted #555;\n");
    fprintf(output_file, "\t\t\t padding: 20px 20px 20px 0;\n");
    fprintf(output_file, "\t\t}\n");

    fprintf(output_file, "\t\tbody {\n");
    fprintf(output_file, "\t\t\t padding: 20px;\n");
    fprintf(output_file, "\t\t\t display: flex;\n");
    fprintf(output_file, "\t\t\t align-items: center;\n");
    fprintf(output_file, "\t\t\t justify-content: center;\n");
    fprintf(output_file, "\t\t}\n");

    fprintf(output_file, "\t\tbody, html {\n");
    fprintf(output_file, "\t\t\t height: 100%;\n");
    fprintf(output_file, "\t\t}\n");

    fprintf(output_file, "\t</style>\n");

    fprintf(output_file, "</head>\n");
    fprintf(output_file, "<body>\n");

    fprintf(output_file, "\t<svg viewBox=\"0 0 500 500\" class=\"chart\">\n");

    fprintf(output_file, "\t\t<polyline\n");
    fprintf(output_file, "\t\t\tfill=\"none\"\n");
    fprintf(output_file, "\t\t\tstroke=\"#0074d9\"\n");
    fprintf(output_file, "\t\t\tstroke-width=\"2\"\n");
    fprintf(output_file, "\t\t\tpoints=\"\n");

    int num_s = 0;

    for (int i = 0; i < 31; i++)
    {
        num_s = num_s + 20;
        int s_num = round(initial_state.S * 500);

        fprintf(output_file, "\t\t\t%d, %d\n", num_s, s_num);

        sir_model_s(&initial_state, b, y);
    }

    fprintf(output_file, "\t\t\t\"\n");

    fprintf(output_file, "\t\t/>\n");

    fprintf(output_file, "\t\t<polyline\n");
    fprintf(output_file, "\t\t\tfill=\"none\"\n");
    fprintf(output_file, "\t\t\tstroke=\"#FF0000\"\n");
    fprintf(output_file, "\t\t\tstroke-width=\"2\"\n");
    fprintf(output_file, "\t\t\tpoints=\"\n");

    int num_i = 0;

    for (int i = 0; i < 31; i++)
    {
        num_i = num_i + 20;
        int i_num = round(initial_state.I * 500);

        fprintf(output_file, "\t\t\t%d, %d\n", num_i, i_num);

        sir_model_i(&initial_state, b, y);
    }

    fprintf(output_file, "\t\t\t\"\n");

    fprintf(output_file, "\t\t/>\n");

    fprintf(output_file, "\t</svg>\n");

    fprintf(output_file, "</body>\n");
    fprintf(output_file, "</html>\n");

    return 0;
}
