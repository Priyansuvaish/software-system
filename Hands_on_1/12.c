/*
 Name : 12.c
Author : Priyanshu Vaish
Description : Write a program to find out the opening mode of a file. Use fcntl.
Date: 9th Sep, 2023.
*/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
int main(){
	int fd=open("employee.txt",O_RDONLY);
	if(fd==-1){printf("file not exist");return 0;}
	int c = O_ACCMODE & fcntl(fd,F_GETFL);
	if (c==O_RDONLY)printf("read only mode");
	else if(c==O_WRONLY)printf("write only mode");
	else if(c==O_RDWR)printf("read and write");
	else printf("not matched");
	close(fd);
}
