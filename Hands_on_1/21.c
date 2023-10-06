/*
 Name : 21.c
Author : Priyanshu Vaish
Description : Write a program, call fork and print the parent and child process id.
Date: 9th Sep, 2023.
*/
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
int main(){
	if(fork()){
	printf("The parent id is %d", getpid());
	}
	else{
	printf("The child process id is %d\n", getpid());
	}
	wait(0);
}
