#ifndef MATRIX_H
#define MATRIX_H

#include<stdio.h>
#include<stdlib.h>

typedef struct t_matrix {
    float **coeffs;
    size_t rows;
    size_t cols;
} t_matrix;

void init_matrix(t_matrix *m, size_t rows, size_t cols);
t_matrix init_matrix2(size_t rows, size_t cols);
void free_matrix(t_matrix *m);
void print_matrix_cli(t_matrix *m);
void input_matrix_cli(t_matrix *m);
t_matrix product(t_matrix *m1, t_matrix *m2);

#endif

