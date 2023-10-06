/*
 Name : 3.c
Author : Priyanshu Vaish
Description : Write a program to create a file and print the file descriptor value. Use creat ( ) system call
Date: 9th Sep, 2023.
*/

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
int main(){
	int fd=creat("filecreate", 0644);
	printf("%d",fd);
	close(fd);
}
