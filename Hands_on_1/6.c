/*
 Name : 6.c
Author : Priyanshu Vaish
Description : Write a program to take input from STDIN and display on STDOUT.
Date: 9th Sep, 2023.
*/
#include <stdio.h>
#include <unistd.h>
int main(){
	int a;
	write(STDOUT_FILENO,"enter the number\n",18);
	read(STDIN_FILENO,&a,sizeof(a));
	write(STDOUT_FILENO,"The number\n",13);
	write(STDOUT_FILENO,&a,sizeof(a));


}
