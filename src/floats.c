#include "../include/floats.h"

/*
 * Initialize a 2D array of floats
 */
void init(float ***f, size_t row, size_t col)
{
    int i;
    int j;

    *f = (float **) malloc(sizeof(float *) * row);

    for (i = 0; i != row; i++)
    {
        printf("%d\n", i);
        *(f)[i] = (float *) malloc(col * sizeof(float));
    }
    for (i = 0; i != row; i++)
    {
        for (j = 0; j != col; j++) {
        printf("%d\n", i);
        f[i][j] = 0;
        }
    }
}

/*
 * Returns a 2D array of floats
 */
float **init2(size_t row, size_t col)
{
    float **f;
    int i;

    f = (float **) malloc(sizeof(float *) * row);

    for (i = 0; i != row; i++)
    {
        (f)[i] = (float *) malloc(sizeof(float) * col);
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
void input_floats_cli(float **f, size_t row, size_t col)
{
    int i;

    for (i = 0; i != row; i++)
    {
        input_row_cli(f[i], col);
    }
}

void input_row_cli(float *f, size_t cols)
{
    int j;

    for (j = 0; j != cols; j++)
    {
        printf("[%d] : ", j);
        scanf(" %f", &f[j]);
    }
}

/*
 * Prints a 2D array of floats in the terminal
 */
void print_floats_cli(float **f, size_t row, size_t col)
{
    int i;
    int j;

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
        if (i + 1 != row) printf(", \n");
    }

    printf("]\n");
}

