#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include"buf.h"
#include<signal.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>
#include<sys/ipc.h>
#include<sys/sem.h>

//#define MAX_USR 3
req got_data;
sem_t sem_id;
void *pthread_func(void *);


int main()
{
int ret,fd,pro_fd;
char temp_pid[4];
pthread_t th;
pthread_attr_t att;

	if(access("./Wfifo",F_OK) == -1){
		if(mkfifo("./Wfifo",0777) != 0)
		{
			perror("Wfifo fails\n");
			exit(EXIT_FAILURE);
		}
	}
	if(access("./Rfifo",F_OK) == -1){
		if(mkfifo("./Rfifo",0777) != 0)
		{
			perror("Rfifo fails\n");
			exit(EXIT_FAILURE);
		}
	}
	
	if(pthread_attr_setdetachstate(&att,PTHREAD_CREATE_DETACHED) != 0){
		printf("ERROR: pthread_attr_setdetachable fails\n");
		exit(EXIT_FAILURE);
	}
	if(pthread_attr_init(&att) != 0){
		printf("ERROR: pthread_attr_init fails\n");
		exit(EXIT_FAILURE);
	}

	if(sem_init(&sem_id,0,1) != 0){
		printf("ERROR: sem_init fails\n");
		exit(EXIT_FAILURE);
	}

	fd = open("Wfifo",O_RDONLY|O_NONBLOCK);
	if(fd == -1){
		printf("ERROR: Wfifo open fails\n");
	}
	
	while(1){
		sem_wait(&sem_id);
		ret = read(fd,&got_data,sizeof(got_data));
		printf("%s: %d read %d bytes from %d\n",__FILE__,fd,ret,got_data.pid);
		sem_post(&sem_id);
		if(got_data.opr != '\0')
			pthread_create(&th,&att,(void *)pthread_func,NULL);
		sleep(1);
	}

return 0;
}


void *pthread_func(void *argc)
{
int ret,fd;
	printf("processing request........ %d\n",got_data.pid );
	sem_wait(&sem_id);
	printf("hello1");
	if(got_data.opr == '+')got_data.result = got_data.opr1 + got_data.opr2;
	else if(got_data.opr == '-')got_data.result = got_data.opr1 - got_data.opr2;
	else if(got_data.opr == '*')got_data.result = got_data.opr1 * got_data.opr2;
	else if(got_data.opr == '/')got_data.result = got_data.opr1 / got_data.opr2;
	
//	printf("hello2");
	kill(got_data.pid,SIGUSR2);

//	printf("hello3");
	fd = open("Rfifo",O_WRONLY);
	if(fd == -1){
		printf("ERROR: Rfifo open fails\n");
	}

//	printf("hello4");
	ret = write(fd,&got_data,sizeof(got_data));
	printf("%s: %d write %d bytes on %d\n",__FILE__,fd,ret,got_data.pid);
	close(fd);		
		got_data.opr 	= '\0';
		got_data.opr1	= 0;
		got_data.opr2	= 0;
		got_data.result	= 0;
		got_data.pid	= 0;
		memset(got_data.msg,'\0',sizeof(got_data.msg)) ;

	sem_post(&sem_id);
	pthread_exit("....REQUEST DONE....\n");
}


