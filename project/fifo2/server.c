#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include"buf.h"
#include<signal.h>
#include<string.h>

#define MAX_USR 3
req got_data;
char flag = 0;
int pro_request(char *);

void sig_hand(int sig_no)
{
flag = 1;
int ret,pro_fd,fd;
	printf("%s GOT SIGNAL",__FILE__);
	pro_fd = open("pro_fifo",O_RDONLY);//|O_NONBLOCK);
	ret = read(pro_fd,&got_data,sizeof(req));
	printf("%d: %d REQUEST DONE ......\n",pro_fd,got_data.pid);
	//if(got_data.pid != 0 )
		kill((got_data.pid),SIGUSR1);  // what if i do get got_data.pid non 0 or other unrequired number 
	fd = open("Rfifo",O_WRONLY);
	write(fd,&got_data,sizeof(got_data));
	close(fd);
		got_data.opr 	= '\0';
		got_data.opr1	= 0;
		got_data.opr2	= 0;
		got_data.result	= 0;
		got_data.pid	= 0;
		memset(got_data.msg,'\0',sizeof(got_data.msg)) ;

}


int main()
{
int ret,fd,pro_fd;
char temp_pid[4];
signal(SIGALRM,sig_hand);


	if(access("./Wfifo",F_OK) == -1)
	{
		if(mkfifo("./Wfifo",0777) != 0)
		{
			perror("Wfifo fails\n");
			exit(EXIT_FAILURE);
		}
	}
	if(access("./Rfifo",F_OK) == -1)
	{
		if(mkfifo("./Rfifo",0777) != 0)
		{
			perror("Rfifo fails\n");
			exit(EXIT_FAILURE);
		}
	}
	if(access("./pro_fifo",F_OK) == -1)
	{
		if(mkfifo("./pro_fifo",0777) != 0)
		{
			perror("pro_fifo fails\n");
			exit(EXIT_FAILURE);
		}
	}


	fd = open("Wfifo",O_RDONLY);//|O_NONBLOCK);
	if(fd == -1){
		printf("ERROR: Wfifo open fails\n");
	}

while(1)
{
	ret = read(fd,&got_data,sizeof(got_data));
	printf("%s: %d read %d bytes from %d\n",__FILE__,fd,ret,got_data.pid);
	
	switch(got_data.opr){
		case '+':
			if(pro_request("pro_client1") == -1){
				break;
			}
		break;
		case '-':
			if(pro_request("pro_client2") == -1){
				break;
			}
		break;
		case '*':
			if(pro_request("pro_client3") == -1){
				break;
			}
		break;
		case '/':
			if(pro_request("pro_client4") == -1){
				break;
			}
		break;
	}
	/*if(flag == 1)
	{
		flag = 0;
		printf("%s GOT SIGNAL",__FILE__);
		pro_fd = open("pro_fifo",O_RDONLY);//|O_NONBLOCK);
		ret = read(pro_fd,&got_data,sizeof(req));
		printf("%d: %d REQUEST DONE ......\n",pro_fd,got_data.pid);
		if(got_data.pid != 0 )
			kill((got_data.pid),SIGUSR1);  // what if i do get got_data.pid non 0 or other unrequired number 
		fd = open("Rfifo",O_WRONLY);
		write(fd,&got_data,sizeof(got_data));
		close(fd);
		got_data.opr 	= '\0';
		got_data.opr1	= 0;
		got_data.opr2	= 0;
		got_data.result	= 0;
		got_data.pid	= 0;
		memset(got_data.msg,'\0',sizeof(got_data.msg)) ;
	}*/
	sleep(1);
}

return 0;
}

int pro_request(char *exe)
{
int ret,pro_fd;
char path[20] = "./";

		ret = fork();
		if(ret == -1){
			kill(got_data.pid,SIGINT);
			return -1;
			//sprintf(temp_pid,"%d",got_data.pid);
			//strcpy(got_data.msg,temp_pid);
			//strcat(got_data.msg,"ERR:FORK FAIL");
		}
		else if(ret == 0){
			printf("....processing request of %d\n",got_data.pid);
			strcat(path,exe);
			execl(path,exe,NULL);
			kill(got_data.pid,SIGINT);
			return -1;
			//sprintf(temp_pid,"%d",got_data.pid);
			//strcpy(got_data.msg,temp_pid);
			//strcat(got_data.msg,"ERR:EXECL FAIL");
		}
////////////////////////////////////////////////////////////////////
/////////////////// Yes i need sleep heree??WHY/////////////////////
////////////////////////////////////////////////////////////////////
		sleep(1);
		pro_fd = open("pro_fifo",O_WRONLY);//|O_NONBLOCK);
		if(pro_fd == -1){
			kill(got_data.pid,SIGINT);
			return -1;
			//sprintf(temp_pid,"%d",got_data.pid);
			//strcpy(got_data.msg,temp_pid);
			//strcat(got_data.msg,"ERR:OPEN FAIL");
		}
		
		ret = write(pro_fd,&got_data,sizeof(req));
		printf("%s writes bytes on pro_client(%d): %d\n",__FILE__,pro_fd,ret);
		got_data.opr 	= '\0';
		got_data.opr1	= 0;
		got_data.opr2	= 0;
		got_data.result	= 0;
		got_data.pid	= 0;
		memset(got_data.msg,'\0',sizeof(got_data.msg)) ;

		close(pro_fd);
return 0;
}
