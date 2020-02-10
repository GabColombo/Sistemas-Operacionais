#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define n_gauleses 7
#define tam 17
#define READ 0 
#define WRITE 1

char gauleses[] = "gabriel";

void comer(int id)
{
	sleep(rand() % 3);
	printf("%c (%d) comeu.\n",gauleses[id],id);
}
void pensar(void)
{
	sleep(rand() % 3);
}	

int main(int argc,char *argv[])
{
	int id, channel1,channel2;
	id = atoi(argv[2]);
	channel1 = atoi(argv[1]);
	channel2 = atoi(argv[3]);
	
	char javalis[1],dormir[1];
	while(1)
	{
		read(channel1,javalis,1);
		pensar();
		printf("%c (%d) retirou um javali.\n",gauleses[id],id);
		comer(id);
		if(javalis[0] == 'B')
		{
			dormir[0] = (char)id;
			write(channel2,dormir,1);
		}
		
	}
	return 0;
}
