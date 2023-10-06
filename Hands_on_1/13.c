/*
 Name : 13.c
Author : Priyanshu Vaish
Description : Write a program to wait for a STDIN for 10 seconds using select. Write a proper print statement to
verify whether the data is available within 10 seconds or not (check in $man 2 select).
Date: 9th Sep, 2023.
*/
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h> 
int main(){
	fd_set rd;
	struct timeval t;
	t.tv_sec=10;
	t.tv_usec=0;
	FD_ZERO(&rd);
	FD_SET(STDIN_FILENO,&rd);
	int s=select(1,&rd,NULL,NULL,&t);
	if(s==0)printf("10 sec over");
	else printf("within 10 sec");
}
