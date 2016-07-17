#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include"buf.h"
#include<signal.h>
#include<sys/ipc.h>
#include<sys/sem.h>

#ifndef _SEMUN_H
#define _SEMUN_H
union semun{
	int val;			//value for SETVAL
	struct semid_ds *buf;		//buffer for IPC_STAT, IPC_SET
	unsigned short int *array;	//array for GETALL, SETALL
	struct seminfo *__buf;		//buffer for IPC_INFO
};
#endif

int sem_id;

void semaphore_p()
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op  = -1;
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

int main(int argc, char **argv)
{
int ret,fd;
union semun sem_union;
req cli;

if(argc != 1)
{
	printf("%s INVALID ARGUMENTS\n",__FILE__);
	exit(EXIT_FAILURE);
}

	if(access("./pro_fifo",F_OK) == -1)
	{
		ret = mkfifo("pro_fifo",0777);
		if(ret == -1)
		{
			printf("ERROR: pro_fifo fails\n");
			exit(EXIT_FAILURE);
		}
	}

	sem_id = semget((key_t)234,1,0666|IPC_CREAT);
	sem_union.val = 1;
	if(semctl(sem_id,0,SETVAL,sem_union) == -1)
	{
		printf("ERROR: semctl fails\n");
		exit(EXIT_FAILURE);
	}

semaphore_p();
printf("%s pro_client successfully created\n",__FILE__);
fd = open("pro_fifo",O_RDONLY);
ret = read(fd,&cli,sizeof(cli));
printf("%s bytes read %d, REQUEST: %d %c %d\n",__FILE__,ret,cli.opr1,cli.opr,cli.opr2);
close(fd);
cli.result = cli.opr1 / cli.opr2; 

kill(getppid(),SIGALRM);
sleep(1);
fd = open("pro_fifo",O_WRONLY);
ret = write(fd,&cli,sizeof(cli));
close(fd);
semaphore_v();
//printf("%s bytes write %d, RESULT: %d\n",__FILE__,ret,result);
return 0;
}
