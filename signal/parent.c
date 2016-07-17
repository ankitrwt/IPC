#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int flag= 0;
void sig_catch(int signo) {
	flag=1;
	printf("%s: Got a signal %d\n", __FILE__, signo);
	return;
}


int main() {
	int ret, c;
	int pid, ppid;
	ret = fork();

	printf("I was here-1\n");
	switch(ret) {
		case -1:
			printf("fork failed\n");
			break;
		case 0:
			printf("I was here1\n");
			pid= getpid();
			printf("%s: CHILD PID: %d\n",__FILE__,pid);
			printf("%s: going for exec\n", __FILE__);
			execl("./child", "child", NULL);
			printf("%s: problem with exec\n", __FILE__);
			break;
		default:
			pid = getpid();
			printf("%s:PARENT PID:%d\n",__FILE__, pid);
			break;

	}
	sleep(2);
	signal(SIGINT, sig_catch);
	kill(ret, SIGALRM);
	c=0;
	while(1) {
		if(flag) {
			printf("%s: Sending signal to child\n", __FILE__);
			kill(ret, SIGALRM);
			flag=0;
	//		pause();
		}

		printf("%s: Loop is running: %d\n", __FILE__, c++);	
		sleep(1);

	}
		printf("%s: ======== Parent Exiting Now============\n", __FILE__);	

}
