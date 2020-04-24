#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/*
 * Exercise 1
 *
 * Find the standard streams filenumber with a shell command :
 *
 * find /usr/include/ -type f | xargs grep -in "standard input"
 * find /usr/include/ -type f | xargs grep -in "standard output"
 *
 */

void question41()
{
    printf("STDIN %d\n", fileno(stdin));
    printf("STDOUT %d\n", fileno(stdout));
    printf("STDERR %d\n", fileno(stderr));
}

/**
 * Equivalent to echo "After redirection" > filename
 */
void question42(char *filename)
{
    int fd_file_to_append;

    puts("Before redirection");
    close(STDOUT_FILENO);
    fd_file_to_append = open(filename, O_CREAT | O_WRONLY);
    puts("After redirection");
    close(fd_file_to_append);
}

/**
 * Read a file, and return a char* (to be freed)
 */
char *read_file(char *filename)
{
    int fd_file_to_read;
    char *file_content;
    char *tmp;
    ssize_t content_read;
    size_t total_size;
    int CHUNK_SIZE = 10;

    total_size = 11;

    tmp = NULL;
    tmp = (char *) calloc(11, sizeof(char));

    file_content = NULL;
    file_content = (char *) calloc(1, sizeof(char));

    fd_file_to_read = open(filename, O_CREAT | O_RDONLY);

    do {
        content_read = read(fd_file_to_read, tmp, CHUNK_SIZE);
        total_size = sizeof(char) * (strlen(file_content) + content_read + 1);

        if (strlen(tmp) != content_read)
            tmp = (char *) realloc(tmp, sizeof(char) * (content_read));

        file_content = (char *) realloc(file_content, total_size);
        strcat(file_content, tmp);
    } while (content_read == CHUNK_SIZE);

    free(tmp);
    close(fd_file_to_read);

    return file_content;
}

void write_file(char *filename, char *to_write)
{
    int fd_file_to_write;

    fd_file_to_write = open(filename, O_CREAT | O_WRONLY);
    write(fd_file_to_write, to_write, sizeof(char) * strlen(to_write));
    close(fd_file_to_write);
}

void copy_file(char *filename_tocopy, char *filename_topaste)
{
    char *content;

    content = read_file(filename_tocopy);
    write_file(filename_topaste, content);

    free(content);
}

void question43()
{
    char *help_txt = read_file("help.txt");
    printf("%s", help_txt);
    write_file("bidule.txt", help_txt);
    free(help_txt);
}

int main(int argc, char *argv[])
{
    question41();

    if (argc > 1)
        question42(argv[1]);

    question43();

    return 0;
}

