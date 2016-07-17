#include<stdio.h>
#include<sys/ipc.h>

#define SIZE  50

typedef struct myQueue{
	long type;
	char buf[SIZE];
}msg;


int main()
{
	int msgid;
	msg myMsg;

	msgid = msgget((key_t)333,0666|IPC_CREAT);

	msgrcv(msgid,&myMsg,SIZE,(long)5,0);

printf(myMsg.buf);
//msgctl(msgid,IPC_RMID,0);
return 0;
}
