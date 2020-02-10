#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>
#include <omp.h>

#define cheio 17
#define n_gauleses 7
#define sim 1
#define nao 0

sem_t cozinha, comida, enchendo;
int count = cheio;

char gauleses[] = "gabriel";

void coloca_javali();
void retira_javali();
void come_javali();

void inicializa_semaforos (void)
{
	sem_init(&cozinha, 0, 0);
	sem_init(&enchendo, 0, 0);	
	sem_init(&comida, 0, cheio);
}

void gaules(int param)
{
	while(1)
	{
		retira_javali(param);	
		sleep(rand() % 3);
	}
}

void cozinheiro (void)
{
	while(1)
	{
		coloca_javali();
		
	}

}

void retira_javali(int param)
{
	int come = sim;
	#pragma omp critical
	{
		if(count < 1)
		{	
			sem_post(&cozinha);
			printf("%c (%d) acordou o cozinheiro\n",gauleses[param],param);
			sem_wait(&enchendo);
			come = nao;
			
		}
		else
		{
			sem_wait(&comida);
			count --;
			printf("%c (%d) retirou um javali\n",gauleses[param],param);
			sleep(rand() % 3);
		}
	}
	if (come == sim)
	{
		come_javali(param);	
	}
}

void come_javali(int param)
{
	sleep(rand() % 3);
	printf("%c (%d) comeu\n",gauleses[param],param);

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
	int id;
	inicializa_semaforos();


	#pragma omp parallel num_threads(n_gauleses+1)
	{
		id = omp_get_thread_num();
		
		if(id == 7)
		{
			cozinheiro();
		}
		else
		{
			gaules(id);
		}
	}
	return 0;
}
