// Date: Dec 8, 2015
// This example Explains Orphan State
//*****************************ORPHAN STATE EXAMPLE******************************//
// Parent Process finishes its execution & termination before child process..
// Init Process Adopts Child Process and the Resources doesnt Handed to parent process
// This results Child Process never got terminate because it has been adopted by Init process

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
		var = 20;
		printf("Child=>   ppid: %d, pid: %d\n",getppid(),getpid());
		printf("::%d %d\n",&var,&ret);
	break;
	default:
		var = 10;
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
