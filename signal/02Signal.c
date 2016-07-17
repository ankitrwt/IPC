#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

unsigned char flag;

int main(int argc,char *argv[])
{
int ret,cpid1,cpid2;
char pid[4];
//------------------------------------------
ret = fork();

if(ret == -1)
{
	printf("FORK FAIL\n");
	exit(1);
}

else if(ret == 0)
{	
	cpid1 = getpid();
	flag = 1;
	sleep(2);
}
else
{
	
	ret = fork();
	if(ret == -1)
	{
		printf("FORK FAIL\n");
		exit(1);
	}

	else if(ret == 0)
	{	
		cpid2 = getpid();
		flag = 2;
	}
	else
	{
	}
}
//------------------------------------------

if(flag == 1)
{
	printf("CHILD: PID %d PPID %d\n",cpid1,getppid());
	sprintf(pid,"%d",cpid2);
	execl("./cli1","cli1",pid,NULL);
	printf("EXECL FAIL\n");
}
if(flag == 2)
{
	printf("CHILD: PID %d PPID %d\n",cpid2,getppid());
	sprintf(pid,"%d",cpid1);
	execl("./cli2","cli2",pid,NULL);
	printf("EXECL FAIL\n");
}
//------------------------------------------
printf("PARENT: PID %d PPID %d\n",getpid(),getppid());
printf("Parent EXIT\n");
return 0;
}									
