#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void question11();
void question12();
void question12_mutex();
void question13();
void question14();

#define TURNS 3
#define BARRIERS 5
#define SIZE 10
#define P(x) sem_wait(x)
#define V(x) sem_post(x)

char g_var = 0;
sem_t s1, s2, barrier_semaphore;
sem_t sread, swrite;
pthread_mutex_t m1, m2;
unsigned int g_wcursor, g_rcursor;
unsigned char buffer[SIZE];

int main()
{
    question14();

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

    pthread_mutex_lock(&m1);
    pthread_mutex_lock(&m2);

    pthread_create(&t1, NULL, print_jemes_mutex, NULL);
    pthread_create(&t2, NULL, print_synchronizethreads_mutex, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&m1);
    pthread_mutex_destroy(&m2);
}

void *barrier_thread()
{
    int i;

    printf("[barrier thread] Waiting !");

    for (i = 0; i != BARRIERS; i++)
    {
        P(&barrier_semaphore);
    }

    printf("[barrier thread] I can continue !\n");

    return NULL;
}

void *worker()
{
    int sleep_time;

    srand(pthread_self());
    sleep_time = rand()%5;
    printf("[Worker] Sleeping for %d... ZZZzzZzzzzz...\n", sleep_time);
    sleep(sleep_time);
    printf("[Worker] Woke up !\n");
    V(&barrier_semaphore);

    return NULL;
}

void question13()
{
    int i;
    pthread_t t1, t[BARRIERS];

    sem_init(&barrier_semaphore, 0, 0);

    pthread_create(&t1, NULL, barrier_thread, NULL);
    for (i = 0; i != BARRIERS; i++)
    {
        pthread_create(&(t[i]), NULL, worker, NULL);
    }

    pthread_join(t1, NULL);
    for (i = 0; i != BARRIERS; i++)
    {
        pthread_join(t[i], NULL);
    }

    sem_destroy(&barrier_semaphore);
}

void *read_thread()
{
    P(&sread);
    printf("Character read %c\n", buffer[g_rcursor]);
    g_rcursor = (g_rcursor + 1)%SIZE;
    V(&swrite);

    return NULL;
}

void *write_thread(void *character)
{
    P(&swrite);
    buffer[g_wcursor] = *((unsigned char *) character);
    g_wcursor = (g_wcursor + 1)%SIZE;
    V(&sread);

    return NULL;
}

void init_buffer()
{
    int i;

    for (i = 0; i != SIZE - 1; i++)
        buffer[i] = ' ';
}

void question14()
{
    pthread_t id_read_thread, id_write_thread;
    unsigned char chr[] = "a";

    init_buffer();
    sem_init(&sread, 0, 0);
    sem_init(&swrite, 0, SIZE);

    pthread_create(&id_read_thread, NULL, read_thread, NULL);
    pthread_create(&id_write_thread, NULL, write_thread, (void *) chr);

    pthread_join(id_read_thread, NULL);
    pthread_join(id_write_thread, NULL);

    sem_destroy(&sread);
    sem_destroy(&swrite);
}



