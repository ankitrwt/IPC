#include<stdio.h>
#include<sys/wait.h>
#include<stdlib.h>

int main()
{

int ret,stat = -1;

ret = fork();

	switch(ret)
	{
		case -1:
			printf("ERROR: fork failed\n");
		break;

		case 0:
			sleep(5);	
			printf("Child: PID: %d\n",getpid());
		break;

		default:
			printf("Parent: PID: %d\n", getpid());
			wait(&stat);
			if(WIFEXITED(stat))
			{

			}
			else
			{
				perror("ERROR: failed\n");
				exit(1);
			}
		break;
	}

printf("END\n");
printf("stat = %d\n",stat);

return 0;
}
