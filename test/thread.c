#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

void question11();
void question12();

#define TURNS 3
#define P(x) sem_wait(x)
#define V(x) sem_post(x)

char g_var = 0;
sem_t m1, m2;

int main()
{
    question11();
    question12();
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


void *print_jemes()
{
    printf("Je ");
    V(&m2);
    P(&m1);
    printf("mes ");
    V(&m2);

    return NULL;
}

void *print_synchronizethreads()
{
    P(&m2);
    printf("synchronize ");
    V(&m1);
    P(&m2);
    printf("threads\n");

    return NULL;
}

void question12()
{
    pthread_t t1, t2;

    sem_init(&m1, 0, 0);/* Initialize semaphore to 0 ! */
    sem_init(&m2, 0, 0);

    pthread_create(&t1, NULL, print_jemes, NULL);
    pthread_create(&t2, NULL, print_synchronizethreads, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&m1);
    sem_destroy(&m2);
}

