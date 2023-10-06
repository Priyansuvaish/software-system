/*
 Name : 4.c
Author : Priyanshu Vaish
Description : Write a program to open an existing file with read write mode. Try O_EXCL flag also.
Date: 9th Sep, 2023.
*/
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
int main(){
	int fd=open("copy.c", O_CREAT|O_EXCL|O_RDWR);
	printf("%d",fd);
	close(fd);
}
