#include "../include/matrix.h"

int main()
{
    t_matrix m;
    int rows;
    int cols;

    puts("init_matrix");
    rows = 2;
    cols = 2;

    /*m = init_matrix2(rows, cols);*/
    init_matrix(&m, rows, cols);
    puts("input_matrix_cli");
    input_matrix_cli(&m);
    puts("print_matrix_cli");
    print_matrix_cli(&m);
    puts("free_matrix");
    free_matrix(&m);

    return 0;
}

