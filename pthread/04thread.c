#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

void pthread_func();
char count;
char buf[BUFSIZ];
int run_now = 1;

int main()
{
int ret;
pthread_t th;
void *exit_status;
int print_count1 = 0;

	ret = pthread_create(&th,NULL,(void *)pthread_func,NULL);
	if(ret != 0)
	{
		perror("thread creation fails\n");
		exit(EXIT_FAILURE);
	}
	while(1)//(print_count1++ < 20)
	{
		if (run_now == 1)
		{
			printf("1\n");
			run_now = 2;
		}
		else
		{
			sleep(1);
		}
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
int print_count1 = 0;
	while(1)//(print_count1++ < 20)
	{
		if (run_now == 2)
		{
			printf("2\n");
			run_now = 1;
		}
		else
		{
//			sleep(1);
		}
	}
	pthread_exit("BYE THREAD\n");
	//printf("no of char entered: %d",sizeof(buf));

}




