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

/*
 * Write a string to a file. The file is created, or overwritten. Returns 0 if
 * opening the file failed, else 1.
 */
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

/*
 * Copy the content of a file to another file. The destination file is
 * created if it doesn't exist. If it is successful, it returns 1, else 0.
 */
int copy(char *file_to_copy, char *file_dest)
{
    int success;
    char *content;

    content = NULL;

    content = read(file_to_copy);

    if (NULL == content)
    {
        puts("Could not read file");
        return 0;
    }

    success = write(file_dest, content);

    free(content);

    return success;
}

