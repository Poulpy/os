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

    puts("write");
    write("./test/OwO.txt", "OwO");

    puts("copy");
    copy("./test/test_floats.c", "./test/OmO.txt");

    return 0;
}


