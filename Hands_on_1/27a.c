/*
 Name : 27a.c
Author : Priyanshu  Vaish
Description : Write a program to execute ls -Rl by the following system calls
		a. execl
Date: 9th Sep, 2023.
*/
#include <unistd.h>
#include <stdio.h>

int main() {
    printf("%d",execl("/usr/bin/ls", "ls", "-Rl", NULL));

}
