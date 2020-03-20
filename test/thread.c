#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

void question11();
void question12();
void question12_mutex();

#define TURNS 3
#define P(x) sem_wait(x)
#define V(x) sem_post(x)

char g_var = 0;
sem_t s1, s2;
pthread_mutex_t m1, m2;

int main()
{
    question12_mutex();

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
    V(&s2);
    P(&s1);
    printf("mes ");
    V(&s2);

    return NULL;
}

void *print_synchronizethreads()
{
    P(&s2);
    printf("synchronize ");
    V(&s1);
    P(&s2);
    printf("threads\n");

    return NULL;
}

void question12()
{
    pthread_t t1, t2;

    sem_init(&s1, 0, 0);/* Initialize semaphore to 0 ! */
    sem_init(&s2, 0, 0);

    pthread_create(&t1, NULL, print_jemes, NULL);
    pthread_create(&t2, NULL, print_synchronizethreads, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&s1);
    sem_destroy(&s2);
}

void *print_jemes_mutex()
{
    printf("Je ");
    pthread_mutex_unlock(&m2);
    pthread_mutex_lock(&m1);
    printf("mes ");
    pthread_mutex_unlock(&m2);

    return NULL;
}

void *print_synchronizethreads_mutex()
{
    pthread_mutex_lock(&m2);
    printf("synchronize ");
    pthread_mutex_unlock(&m1);
    pthread_mutex_lock(&m2);
    printf("threads\n");

    return NULL;
}

void question12_mutex()
{
    pthread_t t1, t2;

    pthread_mutex_init(&m1, NULL);
    pthread_mutex_init(&m2, NULL);

    pthread_create(&t1, NULL, print_jemes_mutex, NULL);
    pthread_create(&t2, NULL, print_synchronizethreads_mutex, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&m1);
    pthread_mutex_destroy(&m2);
}

