/*
 Name : 10.c
Author : Priyanshu Vaish
Description : Write a program to open a file with read write mode, write 10 bytes, move the file pointer by 10
bytes (use lseek) and write again 10 bytes.
a. check the return value of lseek
b. open the file with od and check the empty spaces in between the data.
Date: 28th Aug, 2023.
*/
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
