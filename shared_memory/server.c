#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>


struct shm_data{

	int written_by_you;
	char message1[25] = {"HELLO HOW IS IT GOING\n"};
	char message2[25]; //= {"ITS GOING WELL AND GOOD\n"};
};



int main()
{
int shm_id;
struct shm_data *msgs;
void *shm_addr = (void *) 0 ;

	shm_id=shmget((key_t)123,sizeof(struct shm_data),0777|IPC_CREAT);
	if(shm_id == -1){
		printf("ERROR: shget fails\n");
		exit(EXIT_FAILURE);
	}

	shm_addr = shmat(shm_id,(void *)0,0);
	if(shm_addr == (void *)-1){
		printf("ERROR: shmat fails\n");
		exit(EXIT_FAILURE);
	} 
	printf("Memory attached at %X\n", shm_addr);

	msgs = (struct shm_data *)shm_addr;
	msgs->written_by_you = 1;

//	while(!(msgs->written_by_you));
//	printf("got msg: %s",msgs->message1);

	if(shmdt(shm_addr) == -1){
		printf("ERROR: shmdt fails\n");
		exit(EXIT_FAILURE);
	}

	if(shmctl(shm_id,IPC_RMID,0) == -1){
		printf("ERROR: shmctl fails\n");
		exit(EXIT_FAILURE);
	}

return 0;
}
