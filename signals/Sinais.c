#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdlib.h>

int contador = 0;
void conta(int sinalc)
{
	char continua;
	if(contador < 9)
	{
		contador++;
	}
	else
	{
		signal(SIGALRM,SIG_DFL);		
		alarm(5);
		printf("\nReally exit? (y/n)\n");
		scanf(" %c",&continua);
		if (continua == 'y')
		{
			raise(SIGKILL);
		}
		else
		{
			signal(SIGALRM,SIG_IGN);
			contador = 0;
		}
	}


}
void imprime(int sinalz)
{
	printf("\n%d\n",contador);
}

int main(void)
{
	signal(SIGINT,conta);
	signal(SIGTSTP,imprime);
	while(1);
	return 0;
}
