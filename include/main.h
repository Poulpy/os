#ifndef MAIN_H
#define MAIN_H

#define HELP_TEXT "help.txt"
#define OUT_FILE "out.txt"

int parse_args(int argc, char *argv[], char **output_file, char **mat1_file,
               char **mat2_file);
void print_help();

#endif

