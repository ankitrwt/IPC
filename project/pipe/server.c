#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"buf.h"

#define MAX_USR 3

int req_client(char *,char *,int *);
int pro_req (char *,char *,int *,req,int *);

int main()
{
int ret,i,p[6][2];
req add,sub,mul;

char path[3][12] = {"./client1",
		    "./client2",
		    "./client3"
};

char xname[3][10]= {"client1",
		    "client2",
		    "client3"
};


	for(i=0;i<MAX_USR;i++)
	{
		req_client(path[i],xname[i],p[i]);
	}
	printf("%s server starts, PID %d PPID %d\n",__FILE__,getpid(),getppid());

pro_req ("./pro_client1","pro_client1",p[3],add,p[0]);
pro_req ("./pro_client2","pro_client2",p[4],sub,p[1]);
pro_req ("./pro_client3","pro_client3",p[5],mul,p[2]);
sleep(2);
return 0;
}



int req_client(char *path, char *exe, int ln[2])
{
int ret;
char rfd[4],wfd[4];

	if(pipe(ln) == -1)
	{
		perror("pipe fails\n");
		exit(EXIT_FAILURE);
	}
	ret = fork();
	switch(ret){
	case -1:
		perror("fork fails\n");
		exit(EXIT_FAILURE);
	break;
	case 0:
		printf("%s:%s PID %d PPID %d FD: READ %d WRITE %d\n",__FILE__,exe,getpid(),getppid(),ln[0],ln[1]);
		sprintf(rfd,"%d",ln[0]);
		sprintf(wfd,"%d",ln[1]);
		execl(path,exe,rfd,wfd,NULL);
		printf("%s ERROR: execl fails\n",__FILE__);
	break;
	default:
		
	break;
	}
	
return 0;
}


int pro_req (char *path,char *xname,int ln[2],req dat,int p[2])
{
int ret,result;
	ret = read(p[0],&dat,(sizeof(dat)));
	printf("%s bytes read %d REQUEST RECEIVED %d %c %d = ?\n",__FILE__,ret,dat.opr1,dat.opr,dat.opr2);
	req_client(path,xname,ln);
	ret = write(ln[1],&dat,sizeof(dat));
	printf("%s bytes write %d\n",__FILE__,ret);
	wait();
	ret = read(ln[0],&result,sizeof(result));
	printf("%s bytes read %d, got %d\n",__FILE__,ret,result);
	ret = write(p[1],&result,sizeof(result));
	printf("%s bytes write %d\n",__FILE__,ret);

return 0;
}

