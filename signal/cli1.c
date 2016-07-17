#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
char flag1;

void hand1(int sig)
{
	signal(SIGINT,hand1);
	printf("%s: oops got signal %d\n",__FILE__,sig);
	//signal(SIGPIPE,SIG_DFL);
	flag1 = 1;
}


int main(int argc,char *argv[])
{
	int ret,ppid;
	signal(SIGINT,hand1);

if(argc != 2)
{
	printf("INVALID ARGUMENTS\n");
	exit(1);
}

ppid = atoi(argv[1]);
//kill(ppid,SIGALRM);
//sleep(10);
printf("%s: GOT PPID %d\n",__FILE__,ppid);
	while(1)
	{
		printf("Hello I am Child\n");
		pause();
		if(flag1 == 1)
		{
//			sleep(10);
			flag1 =0;
			sleep(5);
			if(kill(ppid,SIGALRM) == -1)
			{
				printf("%s:KILL ERROR\n",__FILE__);
			}
		}
	}

return 0;
}									
