#include<stdio.h>
#include<signal.h>

void sig_catch(int sig_no)
{
	printf("GOT SIGNAL\n");
//	signal(SIGINT,SIG_DFL);
}


int main()
{
printf("MAIN STARTED\n");
signal(SIGINT,sig_catch);

	while(1)
	{
		printf("WHILE LOOP\n");
		sleep(1);
	}

return 0;
}
