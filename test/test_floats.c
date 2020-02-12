#include "../include/floats.h"

int main()
{
    float **f;
    float **f2;
    size_t row;
    size_t col;

    puts("init");
    f = NULL;
    row = 2;
    col = 2;

    /*
    init(&f, row, col);
    puts("input_floats_cli");
    input_floats_cli(f, row, col);*/
    /*puts("print_floats_cli");
    print_floats_cli(f, row, col);
    puts("free_floats");
    free_floats(f, row);
    */

    puts("init2");
    f2 = NULL;
    row = 2;
    col = 2;

    f2 = init2(row, col);
    puts("input_floats_cli");
    input_floats_cli(f2, row, col);
    puts("print_floats_cli");
    print_floats_cli(f2, row, col);
    puts("free_floats");
    free_floats(f2, row);

    return 0;
}

