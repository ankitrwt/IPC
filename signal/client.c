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


int main(int argc, char **argv)
{
signal(SIGUSR1,sig_catch);

while(1)
{
	printf("%s: CHILD'S  LOOP\n",__FILE__);
	sleep(1);
	if(flag == 1){
		flag = 0;
		kill(getppid(),SIGUSR2);
		printf("%s: send signal to %d process\n",__FILE__,getppid());
		pause();
	}
}

return 0;
}
