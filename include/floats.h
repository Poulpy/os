#ifndef FLOATS_H
#define FLOATS_H

#include<stdio.h>
#include<stdlib.h>

float **init2(size_t row, size_t col);
void free_floats(float **f, size_t row);
void init_floats(float ***f, size_t row, size_t col);
void input_floats_cli(float **f, size_t row, size_t col);
void input_row_cli(float *f, size_t cols);
void print_floats_cli(float **f, size_t row, size_t col);

#endif

