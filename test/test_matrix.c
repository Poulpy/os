#include "../include/matrix.h"

void test_atomatrix()
{
    t_matrix m;

    m = atomatrix("test/mat.txt");
    print_matrix_cli(&m);

    free_matrix(&m);
}

int main()
{
    test_atomatrix();
    /*
    t_matrix m;
    t_matrix m2;
    t_matrix m3;
    int rows;
    int cols;

    rows = 2;
    cols = 2;

    puts("init_matrix2");
    m = init_matrix2(rows, cols);

    puts("init_matrix");
    init_matrix(&m2, rows, cols);

    puts("input_matrix_cli");
    input_matrix_cli(&m);
    input_matrix_cli(&m2);

    m3 = product(&m, &m2);

    puts("print_matrix_cli");
    print_matrix_cli(&m);
    print_matrix_cli(&m2);
    print_matrix_cli(&m3);

    puts("free_matrix");
    free_matrix(&m);
    free_matrix(&m2);
    free_matrix(&m3);
    */

    return 0;
}

