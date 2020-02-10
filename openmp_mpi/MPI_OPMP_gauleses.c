#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <omp.h>
#include "mpi.h"

#define javalis 17
#define n_gauleses 7
#define cozinheiro 0
#define gaules 1


char gauleses[] = "gabriel";
char comida[javalis]= "abcdefghijklmnopq";
int count = 0;
int cozinhar = 1;
int tag = 0;

void main (int argc, char * argv[])
{
	int my_rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	
	while(1)
	{

		if(my_rank == cozinheiro)
		{
			MPI_Recv(&cozinhar, sizeof(cozinhar),MPI_INT, gaules, tag, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			count = 0;
			sleep(rand() % 3);
			printf("O cozinheiro fez a comida. \n");
			MPI_Send(&count,sizeof(count),MPI_INT, gaules, tag, MPI_COMM_WORLD);	
		}
		else
		{
			#pragma omp parallel num_threads(n_gauleses)
			{
				int id;
				char c;
				id = omp_get_thread_num();				
				
				#pragma omp critical
				{
					if(count == javalis)
					{
						printf("%c (%d) acordou o cozinheiro.\n",gauleses[id],id);
						MPI_Send(&cozinhar,sizeof(cozinhar),MPI_INT, cozinheiro, tag, MPI_COMM_WORLD);
						MPI_Recv(&count, sizeof(count),MPI_INT, cozinheiro,  		 		 								tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);	
					}
					printf("%c (%d) retirou o javali %c. \n", gauleses[id],id,comida[count]);
					c=count;					
					count++;

				}
				sleep(rand() % 3);
				printf("%c (%d) comeu o javali %c. \n", gauleses[id],id,comida[c]);
				sleep(rand() % 3);
					
			}
		}
	}

	
}
