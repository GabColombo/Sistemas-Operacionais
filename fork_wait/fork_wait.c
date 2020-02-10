#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
	pid_t childpid = 0;
	printf("Processo A nasceu! PID: %ld, PPID: %ld \n",(long)getpid(),(long)getppid()); //Processo A é o inicial
	childpid = fork(); // Cria processo B
	if (childpid > 0)
	{
		waitpid(childpid, NULL, WUNTRACED); // A espera B
	}
	else if (childpid == 0)
	{
		printf("Processo B nasceu! PID: %ld, PPID: %ld \n",(long)getpid(),(long)getppid());
		childpid = fork(); // Cria processo C 
		if (childpid > 0)
		{
			waitpid(childpid, NULL, WUNTRACED); //B espera C
			printf("Sou o B. Vou morrer! PID: %ld, PPID: %ld \n",(long)getpid(),(long)getppid()); 
			exit(2); // B morre quando C retorna
		}
		else if (childpid == 0)
		{
			printf("Processo C nasceu! PID: %ld, PPID: %ld \n",(long)getpid(),(long)getppid());
			printf("Sou o C. Vou morrer! PID: %ld, PPID: %ld \n",(long)getpid(),(long)getppid());
			exit(1); // C morre
		}
	}
	childpid = fork(); // Cria processo D 
	if (childpid > 0)
	{
		waitpid(childpid, NULL, WUNTRACED); // A espera D
	}
	else if (childpid == 0)
	{
		printf("Processo D nasceu! PID: %ld, PPID: %ld \n",(long)getpid(),(long)getppid());
		printf("Sou o D. Vou morrer! PID: %ld, PPID: %ld \n",(long)getpid(),(long)getppid());
		exit(3); // D morre
	}
	childpid = fork(); // Cria processo E
	if (childpid > 0)
	{
		waitpid(childpid, NULL, WUNTRACED); // A espera E
		printf("Sou o A. Vou morrer! PID: %ld, PPID: %ld \n",(long)getpid(),(long)getppid());
		exit(7); // A morre quando E retorna
	}
	else if(childpid == 0)
	{	
		printf("Processo E nasceu! PID: %ld, PPID: %ld \n",(long)getpid(),(long)getppid());
		childpid = fork(); // Cria processo F
		if (childpid > 0)
		{
			waitpid(childpid, NULL, WUNTRACED); // E espera F
			printf("Sou o E. Vou morrer! PID: %ld, PPID: %ld \n",(long)getpid(),(long)getppid());
			exit(6); // E morre quando F retorna
		}
		else if(childpid == 0)
		{	
			printf("Processo F nasceu! PID: %ld, PPID: %ld \n",(long)getpid(),(long)getppid());
			childpid = fork(); // Cria processo G
			if (childpid > 0)
			{
				waitpid(childpid, NULL, WUNTRACED); // F espera G
				printf("Sou o F. Vou morrer! PID: %ld, PPID: %ld \n",(long)getpid(),(long)getppid());
				exit(5); // F morre quando G retorna
			}
			else if(childpid == 0)
			{
				printf("Processo G nasceu! PID: %ld, PPID: %ld \n",(long)getpid(),(long)getppid());
				printf("Sou o G. Vou morrer! PID: %ld, PPID: %ld \n",(long)getpid(),(long)getppid());
				exit(4); // G morre
			}
		}
	}

	return 0;
}
