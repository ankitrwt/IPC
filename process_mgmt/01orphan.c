#include<stdio.h>

// In this example parent will die before child

int main()
{
int ret;
printf("MAIN STARTED\n");  // this statement will execute only once

ret = fork();

switch(ret){
case -1:
	printf("ERROR: fork fail\n");
break;
case 0:
	sleep(1);
	printf("Hello I am Child  My pid is %d & my ppid is %d\n",getpid(),getppid());
break;
default:
	printf("Hello I am Parent My pid is %d & my ppid is %d\n",getpid(),getppid());
break;

}

printf("******BYE*******\n");
return 0;
}
