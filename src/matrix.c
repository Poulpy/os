#include "matrix.h"

/*
 * Initialize a matrix
 */
void init_matrix(t_matrix *m, size_t rows, size_t cols)
{
    float **f;

    f = NULL;
    init_floats(&f, rows, cols);

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
    f = init_floats2(rows, cols);

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

/*
 * Returns the product of 2 matrixes. The number of rows of the first matrix
 * must equal to the number of columns of the second
 * Don't forget to free
 */
t_matrix product(t_matrix *m1, t_matrix *m2)
{
    int i;
    int j;
    int z;
    int sum;
    t_matrix m3;

    if (m1->rows != m2->cols) return m3;

    init_matrix(&m3, m1->rows, m2->cols);

    for (i = 0; i != m1->rows; i++)
    {
        for (j = 0, sum = 0; j != m2->cols; j++)
        {
            for (z = 0; z != m1->cols; z++)
            {
                sum += m1->coeffs[i][z] * m2->coeffs[z][j];
            }

            m3.coeffs[i][j] = sum;
        }
    }

    return m3;
}

/*
 * Replaces all characters rep by character cop in a string str
 */
void replace(char *str, char rep, char cop)
{
    while (*str != '\0')
    {
        if (*str == rep)
        {
            *str = cop;
        }
        str++;
    }
}

/*
 * Returns the index of the first occurence of a character
 * in a string
 */
int get_index(char *str, char chr)
{
    char *c;

    c = strchr(str, chr);
    return (int) (c - str);
}

/*
 * Returns a matrix according to the following format
 * rows cols
 * coeff1 coeff2
 * coeff3 coeff4
 */
t_matrix atomatrix(char *contents)
{
    int cols;
    int current;
    int i;
    int j;
    int rows;
    t_matrix m;

    /*
     * Getting the number of rows and the number of cols
     */
    sscanf(contents, "%d %d", &rows, &cols);

    m = init_matrix2(rows, cols);

    current = get_index(contents, '\n') + LINE_SEPARATOR_SIZE;

    /*
     * Replacing all line endings by blanks, for simplicity
     * TODO for windows, replace(string, string, char) (because \r\n is TWO
     * char (so string) not one : replace(contents, LINE_SEPARATOR, ' ');
     */
    replace(contents, '\n', ' ');

    for (i = 0; i != rows; i++)
    {
        for (j = 0; j != cols; j++)
        {
            /* scanning the coefficient */
            sscanf(contents + current, "%f", &(m.coeffs[i][j]));

            /* moving to the next word, right after a space */
            current += get_index((contents + current), ' ') + 1;
        }
    }

    return m;
}

/*
 * Returns a char* representing a matrix
 * see atomatrix
 */
char *matrixtoa(t_matrix *m)
{
    int i;
    int j;
    char *buf;
    char coefficient_value[COEFF_SIZE] = "";

    buf = NULL;

    buf = (char *) malloc(sizeof(char) * RANDOM_SIZE);

    /*
     * Here we generate the string with the number of rows and the number of columns
     * There is no flag for unsigned int and size_t, we have to convert it to an unsigned long
     */
    sprintf(buf, "%lu %lu", (unsigned long) m->rows, (unsigned long) m->cols);

    /* strlen exludes the \0, so you add 1 */
    buf = (char *) realloc(buf, sizeof(char) * (strlen(buf) + LINE_SEPARATOR_SIZE + 1));
    strcat(buf, LINE_SEPARATOR);

    for (i = 0; i != m->rows; i++)
    {
        for (j = 0; j != m->cols; j++)
        {
            /* Converting the coefficient to a string */
            sprintf(coefficient_value, "%.2f", m->coeffs[i][j]);

            buf = (char *) realloc(buf, sizeof(char) * (strlen(buf) + strlen(coefficient_value) + 1));
            strcat(buf, coefficient_value);

            /* If this is not the last coefficient, we add a space */
            if (j != m->cols - 1)
            {
                buf = (char *) realloc(buf, sizeof(char) * (strlen(buf) + strlen(coefficient_value) + 1));
                strcat(buf, " ");
            }
        }

        /* We add a newline because it is the end of a row */
        buf = (char *) realloc(buf, sizeof(char) * (strlen(buf) + LINE_SEPARATOR_SIZE + 1));
        strcat(buf, LINE_SEPARATOR);
    }

    return buf;
}

