/*
 Name : 27d.c
Author : Priyanshu Vaish
Description : Write a program to execute ls -Rl by the following system calls
	d. execv
Date: 9th Sep, 2023.
*/
#include <unistd.h>
#include <stdio.h>


int main() {
	char *const argv[]={"ls", "-Rl", NULL};
    printf("%d",execv("/usr/bin/ls", argv));

}
