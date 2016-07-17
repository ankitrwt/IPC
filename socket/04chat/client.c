#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<pthread.h>

void pthread_func(void *);
struct data{
	char user_name[10];
	char conn_name[10];
	char msg[1024];
};
	   
typedef struct data  data_node;
char my_name[10];
int sockfd;
struct sockaddr_in address;

int main(int argc,char **argv)
{

// 1st argument is user name
// 2nd argument is connection name 
pthread_t th;
data_node got_msg;
strncpy(my_name,argv[1],10);

	sockfd = socket(AF_INET,SOCK_STREAM,0);

	address.sin_family = AF_INET;
	address.sin_port   = htons(5566);
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	pthread_create(&th,NULL,(void *)pthread_func,(void *)argv[2]);
	while(1){
		while((connect(sockfd,(struct sockaddr *)&address,sizeof(struct sockaddr_in))) == -1);
		read(sockfd,&got_msg,sizeof(got_msg));
		printf("%s: %s\ntype msg: ",got_msg.user_name,got_msg.msg);
	}

close(sockfd);
return 0;
}

void pthread_func(void *argc){
data_node send_msg;

while(1){
	printf("type msg: ");
	scanf(" %[^\n]s",send_msg.msg);
	strncpy(send_msg.user_name,my_name,10);
	strncpy(send_msg.conn_name,(char *)argc,10);
	while((connect(sockfd,(struct sockaddr *)&address,sizeof(struct sockaddr_in))) == -1);
	write(sockfd,&send_msg,sizeof(send_msg));
}

}
