/*
 Name : 25.c
Author : Priyanshu Vaish
Description : Write a program to create three child processes. The parent should wait for a particular child (use
waitpid system call).
Date: 9th Sep, 2023.
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main(){
	int i=fork();
	int j=fork();
	int status;
	if(i==0 && j!=0){
		printf("This child 1 is executing\n");
		sleep(5);
		printf("child 1 is exiting\n");
		exit(0);
	}
	if(i==0 && j==0){
		printf("This child 2 is executing\n");
		sleep(10);
		printf("child 2 is exiting\n");
		exit(0);
	}
	if(i!=0 && j==0){
		printf("This child 3 is executing\n");
		sleep(15);
		printf("child 3 is exiting\n");
		exit(0);
	}
		printf("Parent is waiting\n");
		waitpid(j,&status,0);
		printf("parent exiting\n");
}
