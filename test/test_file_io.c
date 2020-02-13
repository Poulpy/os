#include "../include/file_io.h"

int main()
{
    char *content;

    content = NULL;

    puts("read");
    content = read("./test/test_floats.c");

    printf("%s\n", content);

    free(content);

    return 0;
}


