#ifndef _CHECKPARAMETER_H_
#define _CHECKPARAMETER_H_

#include <stdio.h>
#include <stdlib.h>

int check_missing_parameter(char* parameter, int count_parameter);
int check_too_many_parameters(char** argv, int i, int count_parameter);

#endif
