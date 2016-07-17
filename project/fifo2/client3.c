#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include"buf.h"
#include<sys/sem.h>
#include<sys/ipc.h>
#include<signal.h>


#ifndef _SEMUN_H
#define _SEMUN_H
union semun {
	int val;     			// value for SETVAL 
	struct semid_ds *buf;		//buffer for IPC_STAT, IPC_SET
	unsigned short int *array;	//array for GETALL, SETALL
	struct seminfo *__buf;		//buffer for IPC_INFO
};
#endif

int sem_id;
int make_fifo(char *);

void semaphore_p()
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op  =-1;
	sem_b.sem_flg =SEM_UNDO;

	if(semop(sem_id,&sem_b,1) == -1)
	{
		printf("ERROR: semop fails\n");
		exit(EXIT_FAILURE);
	}
}



void semaphore_v()
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op  = 1;
	sem_b.sem_flg =SEM_UNDO;

	if(semop(sem_id,&sem_b,1) == -1)
	{
		printf("ERROR: semop fails\n");
		exit(EXIT_FAILURE);
	}
}

void sig_hand(int sig_no)
{
	printf("GOT RESULT: %d\n",getpid());
}

int main()
{
int ret,result,fd;
req cli;
union semun sem_union;
signal(SIGUSR1,sig_hand);

cli.opr = '*';
cli.opr1= 10;
cli.opr2= 5;
cli.pid = getpid();
	 
	 if(make_fifo("Wfifo") == -1){
	 	fprintf(stderr,"Wfifo fails\n");
		exit(EXIT_FAILURE);
	 }
	 if(make_fifo("Rfifo") == -1){
		fprintf(stderr,"Rfifo fails\n");
		exit(EXIT_FAILURE);
	 }

	sem_id = semget((key_t)123,1,0666|IPC_CREAT);
	sem_union.val = 1;
	if(semctl(sem_id,0,SETVAL,sem_union) == -1)
	{
		printf("ERROR: semctl fails\n");
		exit(EXIT_FAILURE);
	}


semaphore_p();
fd = open("Wfifo",O_WRONLY);
if(fd == -1)
{
	printf("ERROR: Wfifo open fails\n");
	exit(EXIT_FAILURE);
}
ret = write(fd,&cli,sizeof(cli));
printf("%d bytes write %d: %d\n",getpid(),fd,ret);
close(fd);
semaphore_v();

//semaphore_p();
pause();
fd = open("Rfifo",O_RDONLY);
if(fd == -1)
{
	printf("ERROR: Rfifo open fails\n");
	exit(EXIT_FAILURE);
}
ret = read(fd,&cli,sizeof(cli));
printf("%d bytes read: %d & GOT: %d %c %d = %d\n",getpid(),ret,cli.opr1,cli.opr,cli.opr2,cli.result);
close(fd);
//semaphore_v();

/*	if(semctl(sem_id,0,IPC_RMID,sem_union) == -1)
	{
		printf("ERROR: semctl fails\n");
		exit(EXIT_FAILURE);
	}

*/
//unlink("Wfifo");
return 0;
}


int make_fifo(char *fname)
{
int ret;
	ret = access(fname,F_OK);
	if(ret == -1)
	{
		ret = mkfifo(fname,0777);
		if(ret == -1)
		{
			printf("ERROR: mkfifo fails\n");
			return -1;
		}
	}
return 0;
}

