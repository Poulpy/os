#ifndef FILE_IO_H
#define FILE_IO_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *read(char *filename);
int copy(char *file_to_copy, char *file_dest);
int write(char *filename, char *content);

#endif


