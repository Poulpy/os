#include <stdio.h>
#include <pthread.h>

void question11();

#define TURNS 3

char g_var = 0;

int main()
{
    question11();
    return 0;
}

void *fct_thread()
{
    char local;

    local = 0;
    g_var++;
    local++;

    printf("global : %d\tlocal : %d\n", g_var, local);

    return NULL;
}

void question11()
{
    int i;
    pthread_t threads[TURNS];

    for (i = 0; i != TURNS; i++)
    {
        pthread_create(&threads[i], NULL, fct_thread, NULL);
    }

    for (i = 0; i != TURNS; i++)
    {
        pthread_join(threads[i], NULL);
    }
}

