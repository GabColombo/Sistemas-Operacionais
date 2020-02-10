#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define READ 0
#define WRITE 1
#define n_gauleses 7
#define tam 17

int main (void)
{
	int pipe1[2],pipe2[2],i;
	char channel1[2],channel2[2];
	pid_t pid,pid_cozinheiro;
	pipe(pipe1);
	pipe(pipe2);


	for(i=0;i<n_gauleses;i++)
	{
		if( (pid=fork()) == 0 )
		{	char id[tam];
			close(pipe1[WRITE]);
			close(pipe2[READ]);
			sprintf(channel1,"%d",pipe1[READ]);
			sprintf(channel2,"%d",pipe2[WRITE]);
			sprintf(id,"%d",i);			

			execl("./pipe_gaules","pipe_gaules",channel1,id,channel2,NULL);

		}
	}

	if( (pid=fork()) == 0 )
	{
		close(pipe1[READ]);
		close(pipe2[WRITE]);
		sprintf(channel1,"%d",pipe1[WRITE]);
		sprintf(channel2,"%d",pipe2[READ]);
		
		execl("./pipe_cozinheiro","pipe_cozinheiro",channel1,channel2,NULL);
	}
	
	while(1);
}
