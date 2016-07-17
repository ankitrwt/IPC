#include <stdio.h>
#include <signal.h>

int flag= 0;
void sig_catch(int signo) {
	flag=1;
	printf("%s: Got a signal %d\n", __FILE__, signo);
	return;
}


int main(int argc, char **argv) {
	int ret,c;
	
	printf("%s: Child started\n", __FILE__);
	signal(SIGALRM, sig_catch);
	
	c=0;
	while(1) {
		if(flag) {
			printf("%s: Sending signal to parent\n", __FILE__);
			kill(getppid(), SIGINT);
			flag=0;
		//	pause();
		}

		printf("%s: Loop is running: %d\n", __FILE__, c++);	
		sleep(1);

	}
		printf("%s: ======== Child Exiting Now============\n", __FILE__);	

}
