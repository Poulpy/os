#include "../include/file_io.h"

char *read(char *filename)
{
    FILE *file;
    char *content;

    file = NULL;

    file = fopen(filename, "r");
    if (file != NULL)
    {
        while (fgets(content, 10, f) != NULL);
        fclose(file);
    }
}
