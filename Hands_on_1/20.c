/*
 Name : 20.c
Author : Priyanshu Vaish
Description : Find out the priority of your running program. Modify the priority with nice command.
Date: 9th Sep, 2023.
*/
#include <sys/resource.h>
#include <unistd.h>
#include <stdio.h>
int main(){
	int process_id = getpid();
	int priority = getpriority(PRIO_PROCESS,0);
	printf("Priority of the process %d",priority);
	nice(-5);
	priority = getpriority(PRIO_PROCESS,0);
	printf("\nPriority of the process after the modified priority %d",priority);

}
