#ifndef FILE_IO_H
#define FILE_IO_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifndef LINE_SEPARATOR
# if defined(__WIN32) || defined(__WIN32__)
#  define LINE_SEPARATOR "\r\n"
#  define LINE_SEPARATOR_SIZE 2
# else
#  define LINE_SEPARATOR "\n"
#  define LINE_SEPARATOR_SIZE 1
# endif
#endif

char *read(char *filename);
int copy(char *file_to_copy, char *file_dest);
int write(char *filename, char *content);

#endif

