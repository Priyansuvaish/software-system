/*

 Name : 16a.c
Author : Priyanshu Vaish
Description : Write a program to perform mandatory locking.
	a. Implement write lock
Date: 9th Sep, 2023.*/
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main(){
	int fd=open("temp.txt",O_WRONLY);
	if(fd==-1)printf("file not exit");
	else{
		struct flock f;
		f.l_type = F_WRLCK;
		f.l_whence = SEEK_SET;
		f.l_start=0;
		f.l_len=0;
		f.l_pid=getpid();
		fcntl(fd,F_SETLKW,&f);
		printf("inside critical section\n");
		getchar();
		f.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&f);
		printf("unlocked");
		close(fd);
	}
}
