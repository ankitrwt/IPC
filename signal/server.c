#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

int flag;

void sig_catch(int sig_no)
{
	printf("%s: GOT SIGNAL %d\n",__FILE__,sig_no);
	flag = 1;
}


int main()
{
int ret;

ret = fork();

switch(ret){
case -1:
	perror("fork fails\n");
	exit(EXIT_FAILURE);
break;
case 0:
	printf("%s: CHILD  pid %d ppid %d\n",__FILE__,getpid(),getppid());
	execl("./client","client",NULL);
	printf("%s: ERROR: excel fails\n",__FILE__);
break;
default:
	printf("%s: PARENT pid %d ppid %d\n",__FILE__,getpid(),getppid());
break;

}

signal(SIGUSR2,sig_catch);
sleep(3);

if(kill(ret,SIGUSR1) == -1)printf("%s: fails\n",__FILE__);
printf("%s: send signal to %d process\n",__FILE__,ret);

while(1)
{
	printf("%s: PARENT'S LOOP\n",__FILE__);
	sleep(1);
	if(flag == 1){
		flag = 0;
		kill(ret,SIGUSR1);
		printf("%s: send signal to %d process\n",__FILE__,ret);
	}
}


return 0;
}
