#include "floats.h"

int main()
{
    float **f;
    float **f2;
    size_t row;
    size_t col;

    f = NULL;
    row = 2;
    col = 2;

    puts("init");
    init_floats(&f, row, col);

    if (f == NULL)
    {
        puts("f is null");
    }
    else
    {
        puts("input_floats_cli");
        input_floats_cli(f, row, col);
        puts("print_floats_cli");
        print_floats_cli(f, row, col);
        puts("free_floats");
        free_floats(f, row);
    }

    f2 = NULL;
    row = 2;
    col = 2;

    puts("init2");
    f2 = init_floats2(row, col);

    if (f2 == NULL)
    {
        puts("f2 is null");
    }
    else
    {
        puts("input_floats_cli");
        input_floats_cli(f2, row, col);
        puts("print_floats_cli");
        print_floats_cli(f2, row, col);
        puts("free_floats");
        free_floats(f2, row);
    }

    return 0;
}

