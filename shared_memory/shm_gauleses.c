#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/shm.h>

#define n_gauleses 7
#define cheio 17
#define sim 1
#define nao 0
#define ADDKEY 111

typedef struct 
{
	sem_t cozinha, enchendo, comida, mutex;
	int count;
}semaforos;


semaforos *jantar;

int shmid, flag = 0;
char *path = "shm";

char gauleses[] = "gabriel";

key_t key = ADDKEY;
pthread_t tid;

void retira_javali();
void come_javali();

void inicializa_shm (void)
{
	shmid = shmget(key, sizeof(semaforos),0);
	if(shmid==-1)
	{
		perror("Erro no shmget\n");
		exit(1);
	}
	jantar = (semaforos *) shmat(shmid,0,flag);

}

void* gaules(void *param)
{
	while(1)
	{
		retira_javali(param);	
		sleep(rand() % 3);
	}
}


void retira_javali(void* param)
{
	int come = sim;
	sem_wait(&jantar->mutex);
	if((jantar->count) == 0)
	{	
		sem_post(&jantar->cozinha);
		printf("%c (%li) acordou o cozinheiro\n",gauleses[(long int)param],(long int)param);
		sem_wait(&jantar->enchendo);
		come = nao;
		
	}
	else
	{
		sem_wait(&jantar->comida);
		(jantar->count)--;
		printf("%c (%li) retirou um javali\n",gauleses[(long int)param],(long int)param);
		sleep(rand() % 3);
	}
	sem_post(&jantar->mutex);
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

int main (void)
{
	long int i;

	inicializa_shm();

	for(i=0;i<n_gauleses;i++)
	{
		pthread_create(&tid,NULL,gaules,(void*) i);
	}

	pthread_join(tid,NULL);

}
