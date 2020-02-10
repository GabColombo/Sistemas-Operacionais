#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "mpi.h"

#define n_gauleses 7
#define javalis 17
#define cozinheiro 7
#define acordar 8

int cozinhar=1;
int id;
int tag = 0;
int count = 0;

char gaules[] = "gabriel";
char comida[javalis]= "abcdefghijklmnopq";


void main (int argc, char * argv[])
{
	int my_rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	
	while(1)
	{
		if(my_rank == cozinheiro)
		{	
			
			MPI_Recv(&cozinhar, sizeof(cozinhar),MPI_INT, acordar, tag, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			count = 0;
			printf("O cozinheiro fez a comida. \n");
			sleep(rand() % 3);
			MPI_Send(&count,sizeof(count),MPI_INT, acordar, tag, MPI_COMM_WORLD);	
			
		}
		else if(my_rank == acordar)
		{
			MPI_Recv(&id, sizeof(id),MPI_INT, MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			
			if(count == javalis)
			{	
				printf("%c (%d) acordou o cozinheiro.\n",gaules[id],id);
				MPI_Send(&cozinhar,sizeof(cozinhar),MPI_INT, cozinheiro, tag, MPI_COMM_WORLD);	
				MPI_Recv(&count, sizeof(count),MPI_INT, cozinheiro,tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			}
			MPI_Send(&count, sizeof(count),MPI_INT,id,tag,MPI_COMM_WORLD);
			count++;
			
		}
		else
		{
			id = my_rank;
			MPI_Send(&id,sizeof(id),MPI_INT, acordar, tag, MPI_COMM_WORLD);	
			MPI_Recv(&count,sizeof(count),MPI_INT,acordar,tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			printf("%c (%d) retirou um javali. \n", gaules[id],id);
			sleep(rand() % 3);
			printf("%c (%d) comeu o javali %c. \n", gaules[id],id, comida[count]);
			sleep(rand() % 3);
		}
	}

	MPI_Finalize();
}
