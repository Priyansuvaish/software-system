/*
 Name : 29.c
Author : Priyanshu Vaish
Description : Write a program to get scheduling policy and modify the scheduling policy (SCHED_FIFO,
SCHED_RR).
Date: 9th Sep, 2023.
*/
#include<unistd.h>
#include<stdio.h>
#include<error.h>
#include <sched.h>
int main(){
	struct sched_param p;
	p.sched_priority = 2;
	pid_t pid =getpid();
	char *a[]={"other","fifo","round robin"};
	printf("Default policy %s\n", a[sched_getscheduler(0)]);
	sched_setscheduler(pid,SCHED_FIFO,&p);
	printf("changed policy %s", a[sched_getscheduler(0)]);
}
