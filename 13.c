#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h> 
int main(){
	fd_set rd;
	struct timeval t;
	t.tv_sec=10;
	t.tv_usec=0;
	FD_ZERO(&rd);
	FD_SET(STDIN_FILENO,&rd);
	int s=select(1,&rd,NULL,NULL,&t);
	if(s==0)printf("10 sec over");
	else printf("within 10 sec");
}
