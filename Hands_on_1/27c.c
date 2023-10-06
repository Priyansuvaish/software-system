/*
 Name : 27c.c
Author : Priyanshu  Vaish
Description : Write a program to execute ls -Rl by the following system calls
		c. execle
Date: 9th Sep, 2023.
*/
#include <unistd.h>
#include <stdio.h>

int main() {
    printf("%d",execle("/usr/bin/ls", "ls", "-Rl", NULL));

}
