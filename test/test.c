#include<stdio.h>




int main(){
char buf[20];
int ret;

ret = read(0,buf,sizeof(buf));
printf("ret : %d\n",ret);

ret = write(1,buf,sizeof(buf));
printf("ret : %d\n",ret);

return 0;

}
