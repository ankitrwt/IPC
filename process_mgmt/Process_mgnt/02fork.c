// Date: Dec 8, 2015
// This Example shows that all the variable hve different addresses in memory 
// for child and parent.
// COW(copy on write) data is same if data is not changed by any of the process. 
// If data is changed another copy is formed

// Plus Thsi example Explains Zombie State
//*************************ZOMBIE STATE EXAMPLE*********************************//
// Child Process finishes Before Parent Process.... 
// Child Process finishes its execution the termination of child has to be executed..
// when parent process runs the termination section of child process comes out of Zombie
// Termination of child process is depends on parent process child process remains in
// Zombie/Defunc state untill parent process terminates

#include<stdio.h>
#include<sys/types.h>



int main()
{
pid_t ret;
int var,i;

	ret = fork();

	switch(ret)
	{
	case -1:
		printf("ERROR: fork failed...\n");
	break;

	case 0:
		var = 10;
		printf("Child=>   ppid: %d, pid: %d\n",getppid(),getpid());
		printf("::%d %d\n",&var,&ret);
	break;
	default:
		var = 20;
		printf("Parent=>  ppid: %d, pid: %d\n",getppid(),getpid());
		printf("::%d %d\n",&var,&ret);
	break;

	}
	printf("var add: %d, var val: %d\n",&var,var);

	for(i=0;i<var;i++)
	{
		if(ret == 0)
		{	
			printf("Child=>   ppid: %d, pid: %d\n",getppid(),getpid());
		}
		else
		{
			printf("Parent=>  ppid: %d, pid: %d\n",getppid(),getpid());
		}
	sleep(1);

	}

	printf("Main End\n");
	return 0;
}
