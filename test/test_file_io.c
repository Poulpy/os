#include "../include/file_io.h"

int main()
{
    char *content;

    content = NULL;

    puts("read");
    content = read("./test/test_floats.c");

    if (NULL != content)
    {
        printf("%s\n", content);
    }

    free(content);

    write("./test/OwO.txt", "OwO");

    return 0;
}


