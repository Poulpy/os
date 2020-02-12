#include "../include/floats.h"
#include "../include/matrix.h"

/*
 * Initialize a matrix
 */
void init_matrix(t_matrix *m, size_t rows, size_t cols)
{
    float **f;

    f = NULL;
    f = init2(rows, cols);

    m->coeffs = f;
    m->rows = rows;
    m->cols = cols;
}

/*
 * Returns a matrix initialized. Its coefficients are set to 0
 */
t_matrix init_matrix2(size_t rows, size_t cols)
{
    t_matrix m;
    float **f;

    f = NULL;
    f = init2(rows, cols);

    m.coeffs = f;
    m.rows = rows;
    m.cols = cols;

    return m;
}

/*
 * Free a matrix
 */
void free_matrix(t_matrix *m)
{
    free_floats(m->coeffs, m->rows);
}

/*
 * Lets the user input the values for a matrix,
 * in the terminal
 */
void input_matrix_cli(t_matrix *m)
{
    input_floats_cli(m->coeffs, m->rows, m->cols);
}

/*
 * Prints the coefficients of a matrix in the terminal
 */
void print_matrix_cli(t_matrix *m)
{
    print_floats_cli(m->coeffs, m->rows, m->cols);
}

