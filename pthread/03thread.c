#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

void pthread_func();
char count;

int main()
{
int ret;
pthread_t th;
void *exit_status;

	ret = pthread_create(&th,NULL,(void *)pthread_func,NULL);
	if(ret != 0)
	{
		perror("thread creation fails\n");
		exit(EXIT_FAILURE);
	}
	printf("main waiting for thread to get finish\n");
	sleep(2);
	if(pthread_join(th,&exit_status) != 0)
	{
		perror("join fails\n");
		exit(EXIT_FAILURE);
	}
	
	printf("%s",(char *)exit_status);

return 0;
}


void pthread_func()
{
int ret;
pthread_t th;
void *exit_status;
	if(count > 50)
	{
		pthread_exit("Bye\n");
	}

	count++;
	ret = pthread_create(&th,NULL,(void *)pthread_func,NULL);
	if(ret != 0)
	{
		perror("thread creation fails\n");
		exit(EXIT_FAILURE);
	}
	printf("th %d waiting for thread to get finish\n",count);
	sleep(2);
	if(pthread_join(th,&exit_status) != 0)
	{
		perror("join fails\n");
		exit(EXIT_FAILURE);
	}
	
	printf("%s",(char *)exit_status);
}




