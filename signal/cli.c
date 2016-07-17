#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
char flag1;

void hand1(int sig)
{
	printf("%s: oops got signal %d\n",__FILE__,sig);
	flag1 = 1;
}


int main(int argc,char *argv[])
{
	int ret,ppid;
	signal(SIGINT,hand1);

	printf("%s THIS IS CHILD\n",__FILE__);
	while(1)
	{
		if(flag1 == 1)
		{
			kill(getppid(),SIGALRM);
			flag1 = 0 ;
			pause();
		}
		printf("Hello I am Child %d P: %d\n",getpid(),getppid());
		sleep(1);
	}

return 0;
}									
