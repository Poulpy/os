#include <stdio.h>

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

int main()
{
    question41();

    return 0;
}

