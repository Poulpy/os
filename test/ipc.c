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




/*
void send_pid_message()
{
    pid_t pid;
    int producer_tube;

    pid = getpid();
    printf("[prod] pid %d\n", pid);

    producer_tube = open("producer", O_CREAT | O_TRUNC | O_RDWR);
    write(producer_tube, (void *) &pid, sizeof(pid_t));
    close(producer_tube);
}

pid_t get_pid_message()
{
    pid_t pid;
    int producer_tube;

    producer_tube = open("producer", O_RDWR);
    while (read(producer_tube, (void *) &pid, sizeof(pid_t)) == 0);
    close(producer_tube);

    return pid;
}

void send_message(char *message)
{
    size_t message_size;
    int producer_tube;
    int response;

    message_size = strlen(message);
    producer_tube = open("producer", O_CREAT | O_RDWR);

    printf("[cons] Message size %d\n", message_size);
    write(producer_tube, &message_size, sizeof(size_t));

    do
    {
        read(producer_tube, &response, sizeof(int));
    } while (response != RECEIVED);
    //printf("producer received\n");

    write(producer_tube, message, sizeof(char) * strlen(message));
    close(producer_tube);
}

char *get_message()
{
    char *message_received;
    size_t message_size;
    int producer_tube;
    int response;

    message_size = 0;
    message_received = NULL;
    response = RECEIVED;

    producer_tube = open("producer", O_RDWR);
    while (read(producer_tube, &message_size, sizeof(size_t)) == 0);
    //read(producer_tube, &message_size, sizeof(size_t));
    printf("[prod] Message size %d received\n", message_size);

    //write(producer_tube, &response, sizeof(int));
    //printf("producer received : send RECEIVE msg\n");

    message_received = (char *) calloc(message_size + 1, sizeof(char));

    read(producer_tube, message_received, sizeof(char) * (message_size + 1));
    printf("[prod] Message received : %s\n", message_received);
    close(producer_tube);

    return message_received;
}

*/






void send_pid_message(int pipe)
{
    pid_t pid;

    pid = getpid();
    printf("[prod] pid %d\n", pid);

    write(pipe, (void *) &pid, sizeof(pid_t));
}

pid_t get_pid_message(int pipe)
{
    pid_t pid;

    while (read(pipe, (void *) &pid, sizeof(pid_t)) == 0);
    printf("[cons] The pid is %d\n", pid);

    return pid;
}

void send_message(int pipe, char *message)
{
    size_t message_size;
    int response;

    message_size = strlen(message);

    printf("[prod] Message size %d\n", message_size);
    write(pipe, &message_size, sizeof(size_t));


    write(pipe, message, sizeof(char) * strlen(message));
}

char *get_message(int pipe)
{
    char *message_received;
    size_t message_size;

    message_size = 0;
    message_received = NULL;

    //while (read(pipe, &message_size, sizeof(size_t)) == 0);
    read(pipe, &message_size, sizeof(size_t));
    printf("[cons] Message size %d received\n", message_size);

    message_received = (char *) calloc(message_size + 1, sizeof(char));

    read(pipe, message_received, sizeof(char) * (message_size + 1));
    printf("[cons] Message received : %s\n", message_received);

    return message_received;
}


void producer()
{
    int producer_tube;

    producer_tube = open("producer", O_CREAT | O_TRUNC | O_RDWR);

    send_pid_message(producer_tube);
    send_message(producer_tube, "OwO");

    close(producer_tube);
}

void consumer()
{
    pid_t producer_pid;
    char *message;
    int producer_tube;

    producer_tube = open("producer", O_CREAT | O_RDONLY);
    producer_pid = get_pid_message(producer_tube);

    message = get_message(producer_tube);


    close(producer_tube);
    free(message);
}

void producer_consumer()
{
    pid_t pid, wait_pid;
    int status;


    pid = fork();

    if (pid == -1)
    {
        perror("Couldn't create thread :/\n");
    }
    else if (pid == 0)
    {
        consumer();
    }
    else
    {
        producer();
        while ((wait_pid = wait(&status)) > 0);
    }
}

int main(int argc, char *argv[])
{
    producer_consumer();

    return 0;
}

