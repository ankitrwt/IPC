#include<stdio.h>
#include<stdlib.h>
//#include<sys/socket.h>
#include<netinet/ip.h>
#include<signal.h>
#include<pthread.h>

int sockfd;
void pthread_func(void *);
void sig_hand(int sig_no)
{
	printf("\nserver terminated successfully\n");
	close(sockfd);
	exit(EXIT_SUCCESS);
}

struct data{
	char user_name[10];
	char conn_name[10];
	char msg[1024];
};

struct storefd{
	int user_fd;
	int conn_fd;
	struct data *link;
};

typedef struct data  data_node;
typedef struct storefd link_fd;


link_fd	  client_rec;


int main()
{
int sockfd_client;
int client_address_len;
struct sockaddr_in server_address;
struct sockaddr_in client_address;
signal(SIGINT,sig_hand);
pthread_t th;
char cli_str_fd[4];

	sockfd = socket(AF_INET,SOCK_STREAM,0);
 	
	server_address.sin_family = AF_INET;
 	server_address.sin_port = htons(5566);
 	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
 
	//server_address->sin_family = AF_INET;
	//server_address->sin_port   = htons(5000);
	//server_address->sin_addr.s_addr = htonl(INADDR_ANY); 
	
	bind(sockfd,(struct sockaddr *)&server_address,sizeof(struct sockaddr_in));

	listen(sockfd,5);

	while(1){
		sockfd_client = accept(sockfd,(struct sockaddr *)&client_address,&client_address_len);
		sprintf(cli_str_fd,"%d",sockfd);
		pthread_create(&th,NULL,(void *)pthread_func,(void *)cli_str_fd);	
	}

return 0;
}

void pthread_func(void *argc){

	data_node client_msg;
	read(atoi((char *)argc),&client_msg,sizeof(client_msg));

}
