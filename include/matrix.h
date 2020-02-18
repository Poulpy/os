#ifndef MATRIX_H
#define MATRIX_H

#include<stdio.h>
#include<stdlib.h>
#include "../include/floats.h"
#include "../include/file_io.h"

typedef struct t_matrix {
    float **coeffs;
    size_t rows;
    size_t cols;
} t_matrix;

t_matrix atomatrix(char *filename);
t_matrix init_matrix2(size_t rows, size_t cols);
t_matrix product(t_matrix *m1, t_matrix *m2);
void free_matrix(t_matrix *m);
void init_matrix(t_matrix *m, size_t rows, size_t cols);
void input_matrix_cli(t_matrix *m);
void print_matrix_cli(t_matrix *m);

#endif

