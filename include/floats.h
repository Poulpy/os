#ifndef FLOATS_H
#define FLOATS_H

#include<stdio.h>
#include<stdlib.h>

float **init_floats2(size_t row, size_t col);
int input_floats_cli(float **f, size_t row, size_t col);
int input_row_cli(float *f, size_t cols);
void free_floats(float **f, size_t row);
void init_floats(float ***f, size_t row, size_t col);
void print_floats_cli(float **f, size_t row, size_t col);

#endif

