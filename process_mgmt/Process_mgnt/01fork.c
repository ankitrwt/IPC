// Date: Dec 8, 2015
// Simple Fork Example showing fork return 0 when executed by chiled
// and returns non negative integer when executed by parent process.  




#include<stdio.h>




int main()
{
	int ret;

	ret = fork();          // Splits process into another process

	switch(ret)
	{
	case -1:
		printf("ERROR: fork failed...\n");
	break;

	case 0:               // This case is only executed by child process 
		printf("Child=>   ppid: %d, pid: %d\n",getppid(),getpid());
	break;
	default:	     // This cae is only executed by parent process
		printf("Parent=>  ppid: %d, pid: %d\n",getppid(),getpid());
	break;

	}

	printf("Main End\n"); // This statement is executed by both parent as well chiled process

	return 0;
}
