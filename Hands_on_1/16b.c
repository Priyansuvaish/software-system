/*
 Name : 16b.c
Author : Priyanshu Vaish
Description : Write a program to perform mandatory locking.
	b. Implement read lock
Date: 9th Sep, 2023.
*/#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main(){
	int fd=open("temp.txt",O_RDONLY);
	if(fd==-1)printf("file not exit");
	else{
		struct flock f;
		f.l_type = F_RDLCK;
		f.l_whence = SEEK_SET;
		f.l_start=0;
		f.l_len=0;
		f.l_pid=getpid();
		int i=fcntl(fd,F_SETLKW,&f);
		printf("%d",i);
		printf("inside critical section");
		getchar();
		f.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&f);
		printf("unlocked");
		close(fd);
	}
}
