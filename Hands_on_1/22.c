/*
 Name : 22.c
Author : Priyanshu Vaish
Description : Write a program, open a file, call fork, and then write to the file by both the child as well as the
parent processes. Check output of the file.
Date: 9th Sep, 2023.
*/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
int main(){
	int fd=open("temp.txt",O_CREAT|O_WRONLY|O_APPEND);
	if(fork()){
		write(fd,"This is parent",15);
	}
	else{
		write(fd,"This is child \n",15);
	}
	wait(0);

}
