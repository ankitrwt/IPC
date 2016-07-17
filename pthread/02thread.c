#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>

void pthread_func();
long counter;

char msg[15] = {"Message"};

int main()
{
int ret;
pthread_t th;
void *exit_status;
	ret = pthread_create(&th,NULL,(void *)pthread_func,NULL);
	if(ret != 0)
	{
		perror(" pthread fails \n");
		exit(EXIT_FAILURE);
	}
	printf("waiting to exit thread\n");
	sleep(1);
	ret = pthread_join(th,&exit_status);
	if(ret != 0)
	{
		perror(" join fails\n");
		exit(EXIT_FAILURE);
	}
	printf("Return status of thread: %s",(char *)exit_status);
	printf("msg: %s",msg);
return 0;
}


void pthread_func()
{
	printf("thread created successfully\n");
	strcpy(msg,"msg changed\n");
	pthread_exit("Exit from pthread\n");
}
