#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
int main(){
	int fd_open = open("employee.txt",O_RDWR);
	if(fd_open==-1){printf("file not exit");	return 0;}
	write(fd_open,"aftertenby",10);
	int l= lseek(fd_open,10,SEEK_CUR);
	if(l==-1){printf("out of bound"); return 0;}
	printf("the current offset %d",l);
	write(fd_open,"aftertenbyo",10);
	close(fd_open);
}
