#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
//#include"semun.h"


union semun{
	int val;			/*value for SETVAL */
	struct semid_ds *buf;		/*buffer for IPC_STAT, IPC_SET */
	unsigned short int *array;	/*array for GETALL, SETALL */
	struct seminfo *__buf;		/*buffer for IPC_INFO */
};

 
/*struct sembuf{
	short sem_num;
	short sem_op;
	short sem_flg;
};
*/


	struct sembuf sem_b;


int set_semvalue(void);
int del_semvalue(void);
int semaphore_p(void);
int semaphore_v(void);

int sem_id;

int main()
{
int i,ret;
int pause_time;

	sem_id = semget((key_t)1234, 1, 0666 | IPC_CREAT);

		set_semvalue();

	fork();
	printf("sv = %d\n",sem_b.sem_op);
	for(i=0;i<10;i++)
	{
		semaphore_p();
	printf("sv = %d\n",sem_b.sem_op);
		printf("hello: %d\n",getpid());
		sleep(2);
		semaphore_v();
	printf("sv = %d\n",sem_b.sem_op);
	}
	printf("\n%d − finished\n", getpid());

		del_semvalue();
exit(EXIT_SUCCESS);
}



int set_semvalue(void)
{
	union semun sem_union;
	sem_union.val = 1;
	if(semctl(sem_id, 0, SETVAL, sem_union) == -1)
		return -1;
return 0;
}

int del_semvalue(void)
{
	union semun sem_union;
	if(semctl(sem_id, 0, IPC_RMID, sem_union) == -1)
		return -1;
return 0;
}


int semaphore_p(void)
{
	sem_b.sem_num = 0;
	sem_b.sem_op = -1; /* P() */
	sem_b.sem_flg = SEM_UNDO;
	if(semop(sem_id,&sem_b,1) == -1)
		return -1;
return 0;
}

int semaphore_v(void)
{
	sem_b.sem_num = 0;
	sem_b.sem_op = 1; /* V() */
	sem_b.sem_flg = SEM_UNDO;
	if(semop(sem_id,&sem_b,1) == -1)
		return -1;
return 0;
}
