#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MIN 10
#define MAX 1000
#define RIGHT 2
#define LOWER 3
#define GREATER 4
#define RECEIVED 6

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
        {
            printf("-------------------\n");
            printf("strlen(tmp) %d\n", strlen(tmp));
            printf("-------------------\n");
            tmp = (char *) realloc(tmp, sizeof(char) * (content_read));
            printf("%s\n", tmp);
        }

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

    fd_file_to_write = open(filename, O_CREAT | O_WRONLY, S_IRWXU);
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

int status_tube[2] = { -1, -1 };
int response_tube[2] = { -1, -1 };


void send_to_father(int i)
{
    write(response_tube[1], &i, sizeof(int));
}

void send_to_child(int i)
{
    write(status_tube[1], &i, sizeof(int));
}

void close_tubes()
{
    close(response_tube[0]);
    close(response_tube[1]);
    close(status_tube[0]);
    close(status_tube[1]);
}

int get_father_response()
{
    int i = 0;

    read(status_tube[0], &i, sizeof(int));

    return i;
}

int get_child_response()
{
    int i = 0;

    read(response_tube[0], &i, sizeof(int));

    return i;
}

void child()
{
    int guess, father_response;;
    int lower_limit, upper_limit;
    int has_guessed = 0;

    lower_limit = MIN;
    upper_limit = MAX;
    srand(getpid());

    while (!has_guessed)
    {
        guess = (rand() % (upper_limit - lower_limit)) + lower_limit;
        /*guess = (upper_limit - lower_limit) / 2;*/
        printf("[child] Is it %d ?\n", guess);

        send_to_father(guess);

        father_response = get_father_response();
        printf("[child] Father said something !\n");

        if (father_response == RIGHT)
        {
            printf("[child] Found ! It's %d\n", guess);
            has_guessed = !has_guessed;
        }
        else if (father_response == LOWER)
        {
            printf("[child] It's lower than %d\n", guess);
            upper_limit = guess;
        }
        else
        {
            printf("[child] It's greater than %d\n", guess);
            lower_limit = guess;
        }
    }

}

void father()
{
    int to_guess, child_response;
    int has_guessed = 0;
    int status;
    pid_t wait_pid;

    srand(getpid());
    to_guess = (rand() % (MAX - MIN)) + MIN;

    printf("[father] The number to guess is %d\n", to_guess);

    while (!has_guessed)
    {
        child_response = get_child_response();
        printf("[father] You said %d\n", child_response);

        if (child_response == to_guess)
        {
            has_guessed = !has_guessed;
            send_to_child(RIGHT);
        }
        else if (child_response > to_guess)
        {
            send_to_child(LOWER);
        }
        else
        {
            send_to_child(GREATER);
        }
    }

    while ((wait_pid = wait(&status)) > 0);
}

void open_tubes()
{
    if (pipe(status_tube) == -1 || pipe(response_tube) == -1)
    {
        perror("Damn... There's an error !\n");
    }
}

void mystery_number()
{
    pid_t pid;

    open_tubes();

    pid = fork();

    if (pid == -1)
    {
        perror("Couldn't create thread :/\n");
    }
    else if (pid == 0)
    {
        child();
    }
    else
    {
        father();
    }

    close_tubes();
}





void send_pid_message(int pipe)
{
    pid_t pid;

    pid = getpid();

    write(pipe, (void *) &pid, sizeof(pid_t));
}

pid_t get_pid_message(int pipe)
{
    pid_t pid;

    read(pipe, (void *) &pid, sizeof(pid_t));

    return pid;
}

void send_message(int pipe, char *message)
{
    size_t message_size;

    message_size = strlen(message);

    write(pipe, &message_size, sizeof(size_t));

    write(pipe, message, sizeof(char) * strlen(message));
}

char *get_message(int pipe)
{
    char *message_received;
    size_t message_size;

    message_size = 0;
    message_received = NULL;

    read(pipe, &message_size, sizeof(size_t));

    message_received = (char *) calloc(message_size + 1, sizeof(char));

    read(pipe, message_received, sizeof(char) * (message_size + 1));

    return message_received;
}


void producer(int producer_tube)
{
    send_pid_message(producer_tube);
    send_message(producer_tube, "OwO");
}

void consumer(int producer_tube)
{
    pid_t producer_pid;
    char *message;

    producer_pid = get_pid_message(producer_tube);

    printf("[Consumer] The pid of the consumer is %d\n", producer_pid);

    message = get_message(producer_tube);

    printf("[Consumer] The producer sent : %s\n", message);

    free(message);
}

void producer_consumer()
{
    pid_t pid, wait_pid;
    int status;
    int producer_tube;


    if (mkfifo("producer", 0666) == -1)
    {
        perror("mkfifo is not working");
        exit(1);
    }

    producer_tube = open("producer", O_RDWR);

    pid = fork();

    if (pid == -1)
    {
        perror("Couldn't create thread :/\n");
    }
    else if (pid == 0)
    {
        consumer(producer_tube);
    }
    else
    {
        producer(producer_tube);
        while ((wait_pid = wait(&status)) > 0);
    }

    close(producer_tube);
}

void simulate_shell_pipe(char *cmd1, char *cmd2)
{
    pid_t pid;
    int fd[2] = { -1, -1 };

    pipe(fd);
    pid = fork();

    if (pid == -1)
    {
        perror("Damn... Fork failed");
    }
    else if (pid == 0)
    {
        close(fd[1]);

        dup2(fd[0], STDIN_FILENO);
        system(cmd2);

        exit(EXIT_SUCCESS);
    }
    else
    {
        close(fd[0]);

        dup2(fd[1], STDOUT_FILENO);
        system(cmd1);

        close(STDOUT_FILENO);

        wait(NULL);
    }
}

int main(int argc, char *argv[])
{
    simulate_shell_pipe(argv[1], argv[2]);

    return 0;
}

