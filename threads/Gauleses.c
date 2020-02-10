#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

#define cheio 17
#define n_gauleses 7
#define sim 1
#define nao 0

sem_t cozinha, comida, enchendo;
pthread_mutex_t mutex;
int count = cheio;

char gauleses[] = "gabriel";

pthread_t tid_cozinheiro,tid;

void coloca_javali();
void retira_javali();
void come_javali();

void inicializa_semaforos (void)
{
	pthread_mutex_init(&mutex, NULL);
	sem_init(&cozinha, 0, 0);
	sem_init(&enchendo, 0, 0);	
	sem_init(&comida, 0, cheio);
}

void* gaules(void *param)
{
	while(1)
	{
		retira_javali(param);	
		sleep(rand() % 3);
	}
}

void* cozinheiro(void *param)
{
	while(1)
	{
		coloca_javali();
		
	}

}

void retira_javali(void* param)
{
	int come = sim;
	pthread_mutex_lock(&mutex);
	if(count < 1)
	{	
		sem_post(&cozinha);
		printf("%c (%li) acordou o cozinheiro\n",gauleses[(long int)param],(long int)param);
		sem_wait(&enchendo);
		come = nao;
		
	}
	else
	{
		sem_wait(&comida);
		count --;
		printf("%c (%li) retirou um javali\n",gauleses[(long int)param],(long int)param);
		sleep(rand() % 3);
	}
	pthread_mutex_unlock(&mutex);
	if (come == sim)
	{
		come_javali(param);	
	}
}

void come_javali(void* param)
{
	sleep(rand() % 3);
	printf("%c (%li) comeu\n",gauleses[(long int)param],(long int)param);

}

void coloca_javali(void)
{
	int i;
	sem_wait(&cozinha);
	for(i=0;i<cheio;i++)
	{
		sem_post(&comida);
		count++;
	}
	sleep(rand() % 3);
	printf("Cozinheiro fez a comida\n");
	sem_post(&enchendo);

}

int main (void)
{
	long int i;

	inicializa_semaforos();

	pthread_create(&tid_cozinheiro,NULL,cozinheiro,NULL);

	for(i=0;i<n_gauleses;i++)
	{
		pthread_create(&tid,NULL,gaules,(void*) i);
	}

	pthread_join(tid_cozinheiro,NULL);
}
