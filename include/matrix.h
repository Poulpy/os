#ifndef MATRIX_H
#define MATRIX_H

#include<stdio.h>
#include<stdlib.h>
#include "floats.h"
#include "file_io.h"

#define RANDOM_SIZE 10
#define COEFF_SIZE 10

#ifndef LINE_SEPARATOR
# if defined(__WIN32) || defined(__WIN32__)
#  define LINE_SEPARATOR "\r\n"
#  define LINE_SEPARATOR_SIZE 2
# else
#  define LINE_SEPARATOR "\n"
#  define LINE_SEPARATOR_SIZE 1
# endif
#endif

typedef struct t_matrix {
    float **coeffs;
    size_t rows;
    size_t cols;
} t_matrix;

char *matrixtoa(t_matrix *m);
t_matrix atomatrix(char *contents);
t_matrix init_matrix2(size_t rows, size_t cols);
t_matrix product(t_matrix *m1, t_matrix *m2);
void free_matrix(t_matrix *m);
void init_matrix(t_matrix *m, size_t rows, size_t cols);
void input_matrix_cli(t_matrix *m);
void print_matrix_cli(t_matrix *m);

#endif

