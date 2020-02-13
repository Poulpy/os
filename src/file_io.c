#include "../include/file_io.h"

char *read(char *filename)
{
    FILE *file;
    char *content;
    char letter;
    char char_to_concat[2];

    file = NULL;
    content = NULL;

    file = fopen(filename, "r");

    if (file != NULL)
    {
        /*
        if ((letter = fgetc(file)) != EOF)
        {
            char_to_concat[0] = letter;
            strcat(content, char_to_concat);
        }
        */
            content = (char *) calloc(2, sizeof(char));

        while ((letter = fgetc(file)) != EOF)
        {
            char_to_concat[0] = letter;
            content = (char *) realloc(content, sizeof(char) * (strlen(content) + 2));
            strcat(content, char_to_concat);
        }

        fclose(file);
    }
    else
    {
        puts("No file found");
    }

    return content;
}
