#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

int flag;

	void hand(int sig)
	{
		printf("%s: oops got signal %d\n",__FILE__,sig);
		flag =	1;
	}


int main()
{
int ret,cpid;
char pid[4];
//------------------------------------------
ret = fork();
cpid = ret;
if(ret == -1)
{
	printf("FORK FAIL\n");
	exit(1);
}

else if(ret == 0)
{
	cpid = getpid();	
	printf("%s:CHILD: PID %d PPID %d\n",__FILE__,getpid(),getppid());
	sprintf(pid,"%d",getppid());
	execl("./cli","cli",NULL);
	printf("EXECL FAIL\n");
}
else
{
	printf("%s:PARENT: PID %d PPID %d\n",__FILE__,getpid(),getppid());
}
//------------------------------------------
signal(SIGALRM,hand);

sleep(2);
printf("%s: Signal registered\n",__FILE__);
kill(cpid,SIGINT);
	while(1)
	{
		if(flag == 1)
		{
			kill(cpid,SIGINT);
			flag = 0;
			pause();
		}
		printf("Hello this is main\n");	
		sleep(1);
	}
printf("EXIT FROM %s\n",__FILE__);
return 0;
}

									
