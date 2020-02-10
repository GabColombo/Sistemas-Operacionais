#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

sem_t S1,S2,S3;

pthread_t tid, tidD;

void *A(void *arg)
{
	printf("A - Fui inicializado!\n");
	//sleep(rand() % 5);
	printf("A - Morri!\n");
	sem_post(&S1);
}
void *B(void *arg)
{
	printf("B - Fui inicializado!\n");
	//sleep(rand() % 5);
	printf("B - Morri!\n");
	sem_post(&S2);	
}
void *C(void *arg)
{
	sem_wait(&S1);
	sem_wait(&S2);
	printf("C - Fui inicializado!\n");
	//sleep(rand() % 5);
	printf("C - Morri!\n");
	sem_post(&S3);
	sem_post(&S3);
}
void *D(void *arg)
{
	sem_wait(&S3);
	printf("D - Fui inicializado!\n");
	//sleep(rand() % 5);
	printf("D - Morri!\n");

}
void *E(void *arg)
{
	sem_wait(&S3);
	printf("E - Fui inicializado!\n");
	//sleep(rand() % 5);
	printf("E - Morri!\n");
}

void inicializa_semaforos()
{
	sem_init(&S1,0,0);
	sem_init(&S2,0,0);
	sem_init(&S3,0,0);
}

int main (void)
{
	inicializa_semaforos();
	pthread_create(&tid, NULL, A, NULL);
	pthread_create(&tid, NULL, B, NULL);
	pthread_create(&tid, NULL, C, NULL);
	pthread_create(&tid, NULL, D, NULL);
	tidD=tid;
	pthread_create(&tid, NULL, E, NULL);
	pthread_join(tid, NULL);
	pthread_join(tidD, NULL);
	return 0;
}
