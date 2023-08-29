#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	int fd_open = open("employee.txt",O_RDWR);
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_pid= getpid();
	lock.l_start = 0;
	lock.l_len = 0;
	lock.l_whence = SEEK_SET;
	printf("before entering the critical section \n");
	int r= fcntl(fd_open,F_SETLKW,&lock);
	printf("inside the critical section %d\n",r);
	getchar();
	lock.l_type = F_UNLCK;
	fcntl(fd_open,F_SETLK,&lock);
	printf("unlock");
	close(fd_open);

}
