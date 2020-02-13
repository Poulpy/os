#include "../include/file_io.h"

/*
 * Reads a file and returns a string containing all the content of the file
 * It can return NULL if the file doesn't exist
 * Don't forget to free the char*
 */
char *read(char *filename)
{
    FILE *file;
    char *content;
    char letter;
    char char_to_concat[2] = "";

    file = NULL;
    content = NULL;

    file = fopen(filename, "r");

    if (file == NULL)
    {
        puts("No file found");
    }
    else
    {
        content = (char *) calloc(2, sizeof(char));

        while ((letter = fgetc(file)) != EOF)
        {
            char_to_concat[0] = letter;
            content = (char *) realloc(content, sizeof(char) * (strlen(content) + 2));
            strcat(content, char_to_concat);
        }

        fclose(file);
    }

    return content;
}

int write(char *filename, char *content)
{
    FILE *file;

    file = NULL;

    file = fopen(filename, "w");

    if (NULL == file)
    {
        puts("Could not open file");

        return 0;
    }

    fprintf(file, "%s", content);

    fclose(file);

    return 1;
}

