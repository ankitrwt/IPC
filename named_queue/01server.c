#include<stdio.h>
#include<sys/ipc.h>
#include<string.h>

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

myMsg.type = 5;
strcpy(myMsg.buf,"Hello this is meg queue\n");

msgsnd(msgid,&myMsg,SIZE,0);



return 0;
}
