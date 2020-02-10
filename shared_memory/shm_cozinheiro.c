#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/shm.h>

#define cheio 17
#define ADDKEY 111

typedef struct 
{
	sem_t cozinha, enchendo, comida, mutex;
	int count;

}semaforos;

semaforos *jantar;

int shmid,flag = 0;
char *path = "shm";

key_t key = ADDKEY;

pthread_t tid_cozinheiro;

void coloca_javali();

void inicializa_jantar (void)
{
	sem_init(&jantar->cozinha, 1,0);
	sem_init(&jantar->enchendo, 1,0);
	sem_init(&jantar->mutex, 1, 1);
	sem_init(&jantar->comida, 1, cheio);
	jantar->count = cheio;
}

void inicializa_shm (void)
{
	shmid = shmget(key,sizeof(semaforos), IPC_CREAT|SHM_R|SHM_W);
	if(shmid==-1)
	{
		perror("Erro\n");
		exit(1);
	}

	jantar = (semaforos *) shmat(shmid, 0, flag);
}

void* cozinheiro(void *param)
{
	while(1)
	{
		coloca_javali();
		
	}

}

void coloca_javali(void)
{
	int i;
	sem_wait(&jantar->cozinha);
	while(jantar->count < cheio)
	{		
		sem_post(&jantar->comida);
		(jantar->count++);
	}
	sleep(rand() % 3);
	printf("Cozinheiro fez a comida\n");
	sem_post(&jantar->enchendo);

}


int main (void)
{
	long int i;

	inicializa_shm();
	inicializa_jantar();

	pthread_create(&tid_cozinheiro,NULL,cozinheiro,NULL);

	pthread_join(tid_cozinheiro,NULL);

}
