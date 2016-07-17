#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

void pthread_func();
char count;
char buf[BUFSIZ];
int run_now = 1;
char flag = 0;

int main()
{
int ret;
pthread_t th;
void *exit_status;

	ret = pthread_create(&th,NULL,(void *)pthread_func,NULL);
	if(ret != 0)
	{
		perror("thread creation fails\n");
		exit(EXIT_FAILURE);
	}
	while(1)//(print_count1++ < 20)
	{
		if(scanf("%s",buf) != EOF)
			flag = 1;

		if(flag == 2)
			break;
	}
	printf("main waiting for thread to get finish\n");
	sleep(2);
	if(pthread_join(th,&exit_status) != 0)
	{
		perror("join fails\n");
		exit(EXIT_FAILURE);
	}
	
	printf("%s",(char *)exit_status);

return 0;
}


void pthread_func()
{
int print_count1 = 0;
FILE *fd;

fd = fopen("./text","a+");
	while(1)
	{
		if(flag == 1)
		{
			flag = 0;
			if(strcmp(buf,"exit") == 0)
			{
				pthread_exit("BYE THREAD\n");
				flag  = 2;
			}
			printf("\nno of char entered: %d",strlen(buf));
			fwrite(buf,1,sizeof(buf),fd);
			memset(buf,0,BUFSIZ);
			printf("for exit type exit\n");
		}
	}
}




