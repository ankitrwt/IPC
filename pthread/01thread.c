#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int flag = 1;

void pthread_func();


int main()
{
pthread_t th;

pthread_create(&th,NULL,(void *)pthread_func,NULL);
printf("main started\n");
sleep(2);
while(flag);

return 0;
}


void pthread_func()
{
	printf("thread created \n");
	sleep(5);
	flag = 0;
	pthread_exit("thread exit status");
}
