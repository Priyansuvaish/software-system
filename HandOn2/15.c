/*
Name : 15.c
Author : Priyanshu Vaish
Description : Write a simple program to send some data from parent to the child process.
Date: 1st Oct, 2023.

*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
int main(){
	int fd[2];
	char buff[100];
	char buffer[100];
	if(pipe(fd)==-1){
		perror("Pipe failed !!\n");
		exit(1);
	}
	if(!fork()){
		close(fd[1]);
		if(read(fd[0],&buff,sizeof(buffer))==-1){
			perror("Read Failed !!\n");
			exit(1);
		}
		printf("The message from parent is : %s",buff);

	}
	else{
		close(fd[0]);
		printf("enter the message to parent\n");
		scanf("%s",&buffer);
		if(write(fd[1],&buffer,sizeof(buffer)) == -1){
                        perror("Write Failed !!\n");
                        exit(1);
                }
	}
	wait(0);
	return 0;
}
