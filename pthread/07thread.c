#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<pthread.h>
#include<string.h>
#include<semaphore.h>
#define SIZ BUFSIZ

char buf[SIZ];
sem_t sem_id;

void sig_hand(int sig_no)
{
//	sleep(5);
	printf("got signal: %d\n",sig_no);
	pthread_exit("pthread exited in sig_hand\n");
}

void *pthread_func(void *argv)
{
	sem_wait(&sem_id);
	signal(SIGALRM,sig_hand);
	printf("pthread created\n");
	while(1)
	{
		printf("type %s to exit pthread\n",argv);
		printf("number of characters entered: %d\n",(strlen(buf) - 1));
		sem_wait(&sem_id);
	}
}


int main(int argc, char **argv)
{
pthread_t th;
pthread_attr_t att;
void *exit_status;

	if(sem_init(&sem_id,0,0) == -1){
		printf("ERROR: sem_id fails\n");
		exit(EXIT_FAILURE);
	}

	if(pthread_attr_setdetachstate(&att,/*PTHREAD_CREATE_DETACHED*/PTHREAD_CREATE_JOINABLE
	) == -1){
		printf("ERROR: pthread_attr_setdetachstate fails\n");
		exit(EXIT_FAILURE);
	}
	if(pthread_attr_init(&att) == -1){
		printf("ERROR: pthread_attr_init fails\n");
		exit(EXIT_FAILURE);
	}

	if(pthread_create(&th,&att,pthread_func,(void *)argv[1]) == -1){
		printf("ERROR: pthread_create fails\n");
		exit(EXIT_FAILURE);
	}
	
	while(strncmp(buf,argv[1],4) != 0){
		fgets(buf,sizeof(buf),stdin);
		sem_post(&sem_id);
	}
	pthread_kill(th,SIGALRM);
	if(pthread_join(th,&exit_status) == -1){
		printf("ERROR: pthread_join fails\n");
		exit(EXIT_FAILURE);
	}
	printf("got exit status: %s\n",(char *)exit_status);
printf("MAIN EXIT\n");
return 0;
}
