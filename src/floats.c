#include "floats.h"

/*
 * Initialize a 2D array of floats
 */
void init_floats(float ***f, size_t row, size_t col)
{
    int i;

    *f = (float **) malloc(sizeof(float *) * row);

    for (i = 0; i != row; i++)
    {
        *(*f + i) = (float *) calloc(col, sizeof(float));
    }
}

/*
 * Returns a 2D array of floats
 */
float **init_floats2(size_t row, size_t col)
{
    float **f;
    int i;

    f = (float **) malloc(sizeof(float *) * row);

    if (NULL == f) return NULL;

    for (i = 0; i != row; i++)
    {
        f[i] = (float *) calloc(col, sizeof(float));
    }

    return f;
}


/*
 * Free the memory of a 2D array of floats
 */
void free_floats(float **f, size_t row)
{
    int i;

    for (i = 0; i != row; i++)
    {
        free(f[i]);
    }

    free(f);
}

/*
 * Lets the user input the values for a 2D array of floats,
 * in the terminal
 */
int input_floats_cli(float **f, size_t row, size_t col)
{
    int i;

    if (NULL == f) return 0;

    for (i = 0; i != row; i++)
    {
        input_row_cli(f[i], col);
    }

    return 1;
}

/*
 * Let the user input values for a 1D array of floats
 */
int input_row_cli(float *f, size_t cols)
{
    int j;

    if (NULL == f) return 0;

    for (j = 0; j != cols; j++)
    {
        printf("[%d] : ", j);
        scanf(" %f", &f[j]);
    }

    return 1;
}

/*
 * Prints a 2D array of floats in the terminal
 * [[2.30, 3.44],
 *  [4.00, 2.01]]
 */
void print_floats_cli(float **f, size_t row, size_t col)
{
    int i, j;

    printf("[");
    for (i = 0; i != row; i++)
    {
        printf("[");

        for (j = 0; j != col; j++)
        {
            printf("%.2f", f[i][j]);
            if (j + 1 != col) printf(", ");
        }

        printf("]");
        if (i + 1 != row) printf(", \n ");
    }

    printf("]\n");
}

