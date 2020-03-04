#include "matrix.h"
#include "main.h"

int main(int argc, char *argv[])
{
    char *m1_content, *m2_content, *m3_content;
    char *mat1_file, *mat2_file, *output_file;
    int good_input;
    t_matrix m1, m2, m3;

    output_file = NULL;
    mat1_file = NULL;
    mat2_file = NULL;
    m1_content = NULL;
    m2_content = NULL;
    m3_content = NULL;

    good_input = parse_args(argc, argv, &output_file, &mat1_file, &mat2_file);

    if (good_input)
    {
        printf("%s\n", mat1_file);
        printf("%s\n", mat2_file);
        printf("%s\n", output_file);

        m1_content = read(mat1_file);
        m2_content = read(mat2_file);
        m1 = atomatrix(m1_content);
        m2 = atomatrix(m2_content);
        /* init_matrix(&m3, m1.rows, m1.cols); */
        m3 = product(&m1, &m2);
        m3_content = matrixtoa(&m3);

        print_matrix_cli(&m3);
        write(output_file, m3_content);

        free(mat1_file);
        free(mat2_file);
        free(output_file);
        free(m1_content);
        free(m2_content);
        free(m3_content);
        free_matrix(&m1);
        free_matrix(&m2);
        free_matrix(&m3);
    }

    return 0;
}

int parse_args(int argc, char *argv[], char **output_file, char **mat1_file,
               char **mat2_file)
{
    int good_input;

    good_input = 0;

    if (2 == argc)
    {
        if (strcmp(argv[1], "--help") == 0)
        {
            print_help();
        }
    }
    else if (5 == argc)
    {
        if (strcmp(argv[1], "-o") == 0)
        {
            *output_file = (char *) malloc(sizeof(char) * (strlen(argv[2]) + 1));
            strcpy(*output_file, argv[2]);
            *mat1_file = (char *) malloc(sizeof(char) * (strlen(argv[3]) + 1));
            strcpy(*mat1_file, argv[3]);
            *mat2_file = (char *) malloc(sizeof(char) * (strlen(argv[4]) + 1));
            strcpy(*mat2_file, argv[4]);
            good_input = 1;
        }
        else if (strcmp(argv[3], "-o") == 0)
        {
            *output_file = (char *) malloc(sizeof(char) * (strlen(argv[4]) + 1));
            strcpy(*output_file, argv[4]);
            *mat1_file = (char *) malloc(sizeof(char) * (strlen(argv[1]) + 1));
            strcpy(*mat1_file, argv[1]);
            *mat2_file = (char *) malloc(sizeof(char) * (strlen(argv[2]) + 1));
            strcpy(*mat2_file, argv[2]);
            good_input = 1;
        }
        else
        {
            print_help();
        }
    }
    else if (3 == argc)
    {
        *output_file = (char *) malloc(sizeof(char) * (strlen(OUT_FILE) + 1));
        strcpy(*output_file, OUT_FILE);
        *mat1_file = (char *) malloc(sizeof(char) * (strlen(argv[1]) + 1));
        strcpy(*mat1_file, argv[1]);
        *mat2_file = (char *) malloc(sizeof(char) * (strlen(argv[2]) + 1));
        strcpy(*mat2_file, argv[2]);
        good_input = 1;
    }
    else
    {
        print_help();
    }

    return good_input;
}

/*
 * Prints in the terminal the help
 */
void print_help()
{
    char *help_text;

    help_text = NULL;

    help_text = read(HELP_TEXT);
    printf("%s\n", help_text);

    free(help_text);
}

