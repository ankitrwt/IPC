#include<stdio.h>



int main()
{
int ret,i,count;
printf("MAIN STARTED\n");  // this statement will execute only once

ret = fork();

switch(ret){
case -1:
	printf("ERROR: fork fail\n");
break;
case 0:
	count=10;
	printf("Hello I am Child  My pid is %d & my ppid is %d\n",getpid(),getppid());
break;
default:
	count=15;
	printf("Hello I am Parent My pid is %d & my ppid is %d\n",getpid(),getppid());
break;

}

for(i=0;i<count;i++)
{
sleep(1);
	if(ret == 0)	
		printf("Hello I am Child  My pid is %d & my ppid is %d\n",getpid(),getppid());
	else
		printf("Hello I am Parent My pid is %d & my ppid is %d\n",getpid(),getppid());
}


printf("******BYE*******\n");
return 0;
}
