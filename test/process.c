#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

#define TURNS 10

void question1();

int g_var = 1;

int main()
{
    question1();

    return 0;
}

void question1()
{
    pid_t pid;

    pid = fork();

    if (pid == -1)
    {
        perror("Couldn't create thread");
    }
    else if (pid == 0)/* This is the child's thread */
    {
        g_var *= 2;
        printf("[fils] PID=%d PPID=%d g_var=%d\n", getpid(), getppid(), g_var);
        printf("*** End of process <%d> ***\n", getpid());
    }
    else /* This is the parent's thread */
    {
        g_var += 2;
        printf("[pere] PID=%d PPID=%d g_var=%d\n", getpid(), getppid(), g_var);
        printf("*** End of process <%d> ***\n", getpid());
    }
}

