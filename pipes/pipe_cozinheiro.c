#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define tam 17
#define READ 0
#define WRITE 1

void cozinhar(void)
{
	sleep(rand() % 3);
}

int main(int argc,char *argv[])
{
	int channel1,channel2,i;
	channel1 = atoi(argv[1]);
	channel2 = atoi(argv[2]);
	char javalis[1],dormir[1];
	char gauleses[] = "gabriel";

	while(1)
	{
		printf("Cozinheiro fez a comida\n");
		javalis[0] = 'A';
		for(i=0;i<tam-1;i++)
		{
			write(channel1,javalis,1);
		}
		javalis[0] = 'B';
		write(channel1,javalis,1);
		read(channel2,dormir,1);
		printf("%c (%d) Acordou o cozinheiro.\n",gauleses[(int)dormir[0]],(int)dormir[0]);
		cozinhar();
	}
}
