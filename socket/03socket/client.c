#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>

typedef struct server_data{
	char server_msg[1024];
	char server_name[20];
}server;

int main()
{
server req_1;
int sockfd,len;
struct sockaddr_in address;

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1){
		printf("ERROR: socket fails\n");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_port   = htons(5555);
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	len = sizeof(address);
	if(connect(sockfd,(struct sockaddr *)&address, len) == -1){
		perror("ERROR");
		exit(EXIT_FAILURE);
	}

	while(1)
	{
		strcpy(req_1.server_name,__FILE__);
		printf("%s: ",req_1.server_name);
		scanf(" %[^\n]s",req_1.server_msg);
		write(sockfd,&req_1,sizeof(server));
		sleep(1);
		read(sockfd,&req_1,sizeof(server));
		printf("%s: %s\n",req_1.server_name,req_1.server_msg);
		//close(sockfd);
	}
return 0;
}
