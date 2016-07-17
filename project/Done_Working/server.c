#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include "members.h"

void Req_Client(int *,char *,char *);
void Receive_Req(int *,info *);
void Process_Req(int *,char *,char *, info *,int *);

int p[6][2];
info add,sub,mul;


int main()
{
int i;	
char path[3][12] = {"./clientp",
		    "./clientm",
		    "./clientx"};

char xname[3][10] ={"clientp",
		    "clientm",
		    "clientx"};

	printf("SERVER: %s\n",__FILE__);	

	for(i=0;i<3;i++)
	{
		Req_Client(p[i],path[i],xname[i]);
	}
	printf("%s: Parent\tPID: %d, PPID: %d\n",__FILE__,getpid(),getppid());

while(1)
{
	Receive_Req(p[0],&add);
 	Receive_Req(p[1],&sub);
 	Receive_Req(p[2],&mul);
pause();
}
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
			printf("%s: Child: %s PID: %d, PPID: %d\n",__FILE__,exe,getpid(),getppid());
			sprintf(rfd,"%d",Pipe[0]);		
			sprintf(wfd,"%d",Pipe[1]);
			printf("%s:%s:READ PIPE=%d WRITE PIPE=%d\n",__FILE__,exe,Pipe[0],Pipe[1]);
			execl(path,exe,rfd,wfd,NULL);
			printf("%s: ERROR: excel creation fail\n",__FILE__);
		}
}


void Receive_Req(int Pipe[2],info *dat)
{
int ret,result;
 
ret = read(Pipe[0],dat,(sizeof(info)));
printf("%s:Bytes Read %d :opr = %c,opr1 = %d,opr2 = %d\n",__FILE__,ret,dat->opr,dat->opr1,dat->opr2);

switch(dat->opr){
         case '+':
                 Process_Req(p[3],"./pro_clientp","pro_clientp",&add,p[0]);
         break;
         case '-':
                 Process_Req(p[4],"./pro_clientm","pro_clientm",&sub,p[1]);
         break;
         case '*':
                 Process_Req(p[5],"./pro_clientx","pro_clientx",&mul,p[2]);
         break;
         default:
                 printf("%s: INVALID OPERATOR\n"__FILE__);
         }
 
}


void Process_Req(int Pipe[2],char *P_path,char *P_xname, info *dat,int cPipe[2])
{
 int ret,result;
 Req_Client(Pipe,P_path,P_xname);
 ret = write(Pipe[1],dat,sizeof(info)); 
 printf("%s:Bytes Write %d FD = %d:opr = %c,opr1 = %d,opr2 = %d\n",__FILE__,ret,Pipe[1],dat->opr,dat->opr1,dat->opr2);
 wait();
 ret = read(Pipe[0],&result,sizeof(result));
 printf("%s:Bytes Read %d FD = %d:Got Result = %d\n",__FILE__,ret,Pipe[0],result);
 ret = write(cPipe[1],&result,sizeof(result));
 printf("%s:Bytes write %d FD = %d:Send Result = %d\n",__FILE__,ret,cPipe[1],result);
}

