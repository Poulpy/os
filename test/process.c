#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

#define TURNS 10

void question1();

int g_var = 1;

int main()
{
    question1();

    return 0;
}

void by_2(int *i)
{
    *i *= 2;
}

void by_3(int *i)
{
    *i *= 3;
}

void question1()
{
    pid_t child_pid, wait_pid;
    int i;
    void (*modify_var_by_2) (int *) = &by_2;
    void (*modify_var_by_3) (int *) = &by_3;
    int status;

    status = 0;
    child_pid = fork();

    if (child_pid == -1)
    {
        perror("Couldn't create thread");
    }
    else if (child_pid == 0)/* This is the child's thread */
    {
        printf("[fils] PID=%d PPID=%d g_var=%d\n", getpid(), getppid(), g_var);
        for (i = 0; i != TURNS; i++)
        {
            printf("[fils] <%d> %d g_var=%d\n", getpid(), i, g_var);
            (*modify_var_by_2) (&g_var);
        }
        printf("*** End of process <%d> ***\n", getpid());
    }
    else /* This is the parent's thread */
    {
        printf("[pere] PID=%d PPID=%d g_var=%d\n", getpid(), getppid(), g_var);
        for (i = 0; i != TURNS; i++)
        {
            printf("[pere] <%d> %d g_var=%d\n", getpid(), i, g_var);
            (*modify_var_by_3) (&g_var);
        }
        /*wait(NULL);*/
        while ((wait_pid = wait(&status)) > 0);
        printf("*** End of process <%d> ***\n", getpid());
    }
}

