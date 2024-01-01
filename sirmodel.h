#ifndef _SIRMODEL_H_
#define _SIRMODEL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    double S;
    double I;
    double R;
} EpidemicState;

void make_sir_model(EpidemicState *state, double b, double y);
void real_data_model(FILE* output_file, FILE* real_data_file, int total_number, int* days, int scale, char* color, int s_true, int i_true, int r_true);
void analyze_data_model(EpidemicState* analyze_state, FILE* output_file, int days, int scale, char* color, double b, double y, int s_true, int i_true, int r_true);

#endif
