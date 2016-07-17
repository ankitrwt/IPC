#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>

sem_t sm;
void pthread_func(void);
char buf[BUFSIZ];

int main()
{
int ret;
pthread_t th;
void *exit_status;

	ret = pthread_create(&th,NULL,(void *)pthread_func,NULL);
	if(ret != 0)
	{
		perror("pthread create fails\n");
		exit(EXIT_FAILURE);
	}
	ret = sem_init(&sm,0,0);
	if(ret != 0)
	{
		perror("sem init fails\n");
		exit(EXIT_FAILURE);
	}

	while(strncmp("exit",buf,3) != 0)
	{
		fgets(buf,sizeof(buf),stdin);
		sem_post(&sm);
	}

	printf("waiting pthread to exit...\n");
	ret = pthread_join(th,&exit_status);
	if(ret != 0)
	{
		perror("join fails\n");
		exit(EXIT_FAILURE);
	}
	printf("got status: %s",exit_status);
	sem_destroy(&sm);
return 0;
}

void pthread_func()
{
int ret;
FILE *fd;

	fd = fopen("./test","a+");
	sem_wait(&sm);
	while(strncmp("exit",buf,3) != 0)
	{
		printf("size of string: %d\n",strlen(buf)-1);
		fwrite(buf,1,(sizeof(buf)+1),fd);
		sem_wait(&sm);
	}
	pthread_exit("thread exit status\n");
close(fd);
}
