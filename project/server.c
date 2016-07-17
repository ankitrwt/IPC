#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include "members.h"

void Req_Client(int *,char *,char *);
void Receive_Req();
void Process_Req(char);

int p[6][2];
info add,sub,mul;
char path[3][12] = {"./client+",
		    "./client-",
		    "./clientm"};

char xname[3][10] ={"client+",
		    "client-",
		    "clientm"};


int main()
{
int i;	
	printf("SERVER: %s\n",__FILE__);	

	for(i=0;i<3;i++)
	{
		Req_Client(p[i],path[i],xname[i]);
	}
	printf("%c: Parent\tPID: %d, PPID: %d\n",__FILE__,getpid(),getppid());
	Receive_Req();

return 0;
}



void Req_Client(int Pipe[2],char *path, char *exe)
{
int ret;	
char rfd[4],wfd[4];

		if(pipe(Pipe) == -1)
		{
			perror("ERROR: pipe creation fail\n");
			exit(1);
		}
		ret = fork();
		if(ret == -1)
		{
			perror("ERROR: fork fail\n");
			exit(1);
		}
		else if(ret > 0)
		{
				
		}
		else
		{
			printf("%c: Child: %s PID: %d, PPID: %d\n",__FILE__,exe,getpid(),getppid());
			sprintf(rfd,"%d",Pipe[0]);		
			sprintf(wfd,"%d",Pipe[1]);
			printf("%s:%s:READ PIPE=%d WRITE PIPE=%d\n",__FILE__,exe,Pipe[0],Pipe[1]);
			execl(path,exe,rfd,wfd,NULL);
			printf("%c: ERROR: excel creation fail\n",__FILE__);
		}
}


void Receive_Req()
{
	int ret;
	ret = read(p[0][0],&add,(sizeof(add)));
	printf("%s:Bytes Read %d :opr = %c,opr1 = %d,opr2 = %d\n",__FILE__,ret,add.opr,add.opr1,add.opr2);
	Process_Req(add.opr);
	ret = read(p[1][0],&sub,(sizeof(sub)));
	printf("%s:Bytes Read %d :opr = %c,opr1 = %d,opr2 = %d\n",__FILE__,ret,sub.opr,sub.opr1,sub.opr2);
	Process_Req(sub.opr);
	ret = read(p[2][0],&mul,(sizeof(mul)));
	printf("%s:Bytes Read %d :opr = %c,opr1 = %d,opr2 = %d\n",__FILE__,ret,mul.opr,mul.opr1,mul.opr2);
	Process_Req(mul.opr);
}



void Process_Req(char opr)
{
int ret,result;

switch(opr){
	case '+':
		Req_Client(p[3],"./pro_client+","pro_client+");
		ret = write(p[3][1],&add,sizeof(add));
		printf("%s:Bytes Write %d FD = %d:opr = %c,opr1 = %d,opr2 = %d\n",__FILE__,ret,p[3][1],add.opr,add.opr1,add.opr2);
		wait();
		ret = read(p[3][0],&result,sizeof(result));
		printf("%s:Bytes Read %d FD = %d:Got Result = %d\n",__FILE__,ret,p[3][0],result);
		ret = write(p[0][1],&result,sizeof(result));
		printf("%s:Bytes write %d FD = %d:Send Result = %d\n",__FILE__,ret,p[0][1],result);
					
	break;
	case '-':	
		Req_Client(p[4],"./pro_client-","pro_client-");
		ret = write(p[4][1],&sub,sizeof(sub));
		printf("%s:Bytes Write %d FD = %d:opr = %c,opr1 = %d,opr2 = %d\n",__FILE__,ret,p[4][1],sub.opr,sub.opr1,sub.opr2);
		wait();
		ret = read(p[4][0],&result,sizeof(result));
		printf("%s:Bytes Read %d FD = %d:Got Result = %d\n",__FILE__,ret,p[4][0],result);
		ret = write(p[1][1],&result,sizeof(result));
		printf("%s:Bytes write %d FD = %d:Send Result = %d\n",__FILE__,ret,p[1][1],result);
	break;
	case '*':
		Req_Client(p[5],"./pro_clientm","pro_clientm");
		ret = write(p[5][1],&mul,sizeof(mul));
		printf("%s:Bytes Write %d FD = %d:opr = %c,opr1 = %d,opr2 = %d\n",__FILE__,ret,p[5][1],mul.opr,mul.opr1,mul.opr2);
		wait();
		ret = read(p[5][0],&result,sizeof(result));
		printf("%s:Bytes Read %d FD = %d:Got Result = %d\n",__FILE__,ret,p[5][0],result);
		ret = write(p[2][1],&result,sizeof(result));
		printf("%s:Bytes write %d FD = %d:Send Result = %d\n",__FILE__,ret,p[2][1],result);
	
	break;	
	default:
		printf("%s: INVALID OPERATOR\n"__FILE__);
	}

}
