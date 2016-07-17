#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include"buf.h"

#define MAX_USR 3

unsigned char flag, nxt_time;
int req_clipid[3],i=0;

void sig_hand(int sig_no)
{
	printf("%s: GOT SIGNAL %d ",__FILE__,sig_no);
	if(sig_no == SIGPIPE)
	{
		if((flag&0x10) == 0)
			flag |= (unsigned char)0x11;
		else
			nxt_time |= (unsigned char)1;
	}
	else if(sig_no == SIGALRM)
	{
		if((flag&0x20) == 0)
			flag |= (unsigned char)0x22;
		else
			nxt_time |= (unsigned char)2;
	}
	else if(sig_no == SIGTERM)
	{
		if((flag&0x40) == 0)
			flag |= (unsigned char)0x44;
		else
			nxt_time |= (unsigned char)4;
	}
	printf("flag %x\n",flag);
}



int req_client(char *,char *,int *);
int pro_req (char *,char *,int *,req,int *);
int got_result(int *,int *);

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
	signal(SIGPIPE,sig_hand);
	signal(SIGALRM,sig_hand);
	signal(SIGTERM,sig_hand);

while(1)
{
//---------------------------------------------------------------------------------
	if((flag&0x01) == 1)
	{
		flag &= ~0x01;
		pro_req ("./pro_client1","pro_client1",p[3],add,p[0]);
	}
	else if((flag&0x02) == 2)
	{
		flag &= ~0x02;
		pro_req ("./pro_client2","pro_client2",p[4],sub,p[1]);
	}
	else if((flag&0x04) == 4)
	{
		flag &= ~0x04;
		pro_req ("./pro_client3","pro_client3",p[5],mul,p[2]);
	}
//---------------------------------------------------------------------------------
	if((nxt_time&0x01) == 1)
	{
		nxt_time &= ~0x01;
		flag = 0;
		got_result(p[3],p[0]);
		kill(req_clipid[0],SIGINT);
	}
	else if((nxt_time&0x02) == 2)
	{
		nxt_time &= ~0x02;
		flag = 0;
		got_result(p[4],p[1]);
		kill(req_clipid[1],SIGINT);
	}
	else if((nxt_time&0x04) == 4)
	{
		nxt_time &= ~0x04;
		flag = 0;
		got_result(p[5],p[2]);
		kill(req_clipid[2],SIGINT);
	}

}

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
	req_clipid[i++] = ret;

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
int ret;
	ret = read(p[0],&dat,(sizeof(dat)));
	printf("%s bytes read %d REQUEST RECEIVED %d %c %d = ?\n",__FILE__,ret,dat.opr1,dat.opr,dat.opr2);
	req_client(path,xname,ln);
	ret = write(ln[1],&dat,sizeof(dat));
	printf("%s bytes write %d\n",__FILE__,ret);
return 0;
}

int got_result(int ln[2],int p[2])
{
int ret,result;
	ret = read(ln[0],&result,sizeof(result));
	printf("%s bytes read %d, got %d\n",__FILE__,ret,result);
	ret = write(p[1],&result,sizeof(result));
	printf("%s bytes write %d\n",__FILE__,ret);
return 0;
}
