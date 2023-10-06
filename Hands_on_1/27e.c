/*
 Name : 27e.c
Author : Priyanshu Vaish
Description : Write a program to execute ls -Rl by the following system calls
	e. execvp
Date: 9th Sep, 2023.
*/
#include <unistd.h>
#include <stdio.h>


int main() {
	char *const argv[]={"ls", "-Rl", NULL};
    printf("%d",execvp(argv[0], argv));

}
