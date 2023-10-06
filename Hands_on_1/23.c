/*
 Name : 23.c
Author : Priyanshu Vaish
Description : Write a program to create a Zombie state of the running program.
Date: 9th Sep, 2023.
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

    if(!fork()){ 
        printf("child exit\n");
        exit(0);
    }
	printf("Process is in zombie state");
    sleep(10);
}
